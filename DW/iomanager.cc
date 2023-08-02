#include "iomanager.h"
#include "macro.h"
#include "log.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>

namespace DW {

    static Logger::ptr g_logger = DW_LOG_NAME("system");

    IOManager::FdContext::EventContext& IOManager::FdContext::getContext(IOManager::Event event) {
        switch(event) {
            case IOManager::READ:
                return read;
            case IOManager::WRITE:
                return write;
            default:
                DW_ASSERT(false, "getContext");
        }
        throw std::invalid_argument("getContext invalid event");
    }

    //是重置这个结构体，而不是这个结构体在类中的定位
    void IOManager::FdContext::resetContext(EventContext& ctx) {
        ctx.scheduler = nullptr;
        ctx.fiber.reset();
        ctx.cb = nullptr;
    }

    void IOManager::FdContext::triggerEvent(IOManager::Event event) {
        //同一个事件才触发，不是同一个不能触发
        DW_ASSERT(events & event);
        events = (Event)(events & ~event);
        EventContext& ctx = getContext(event);
        if(ctx.cb) {
            ctx.scheduler->schedule(&ctx.cb);
        } else {
            ctx.scheduler->schedule(&ctx.fiber);
        }
        ctx.scheduler = nullptr;
        return;
    }

    IOManager::IOManager(size_t threads, const std::string& name)
        :Scheduler(threads, name) {
        m_epfd = epoll_create(5000);
        DW_ASSERT(m_epfd > 0);

        //管道是用来触发、tickle的
        int rt = pipe(m_tickleFds);
        DW_ASSERT(!rt);

        epoll_event event;
        memset(&event, 0, sizeof(epoll_event));
        event.events = EPOLLIN | EPOLLET;
        event.data.fd = m_tickleFds[0];

        //无阻塞
        rt = fcntl(m_tickleFds[0], F_SETFL, O_NONBLOCK);
        DW_ASSERT(!rt);

        rt = epoll_ctl(m_epfd, EPOLL_CTL_ADD, m_tickleFds[0], &event);
        DW_ASSERT(!rt);

        contextResize(32);

        start();
    }

    IOManager::~IOManager() {
        stop();
        close(m_epfd);
        close(m_tickleFds[0]);
        close(m_tickleFds[1]);

        for(size_t i = 0; i < m_fdContexts.size(); ++i) {
            if(m_fdContexts[i]) {
                delete m_fdContexts[i];
            }
        }
    }

    void IOManager::contextResize(size_t size) {
        m_fdContexts.resize(size);

        for(size_t i = 0; i < m_fdContexts.size(); ++i) {
            if(!m_fdContexts[i]) {
                m_fdContexts[i] = new FdContext;
                m_fdContexts[i]->fd = i;
            }
        }
    }

    int IOManager::addEvent(int fd, Event event, std::function<void()> cb) {
        FdContext* fd_ctx = nullptr;
        RWMutexType::ReadLock lock(m_mutex);
        if((int)m_fdContexts.size() > fd) {
            fd_ctx = m_fdContexts[fd];
            lock.unlock();
        } else {
            lock.unlock();
            RWMutexType::WriteLock lock2(m_mutex);
            contextResize(fd * 1.5);
            fd_ctx = m_fdContexts[fd];
        }

        FdContext::MutexType::Lock lock2(fd_ctx->mutex);
        if((fd_ctx->events & event)) {
            DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING(
                "addEvent assert fd=", fd,
                " event=", (EPOLL_EVENTS)event,
                " fd_ctx.event=", (EPOLL_EVENTS)fd_ctx->events
            ));

            DW_ASSERT(!(fd_ctx->events & event));
        }

        int op = fd_ctx->events ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
        epoll_event epevent;
        epevent.events = EPOLLET | fd_ctx->events | event;
        epevent.data.ptr = fd_ctx;

        int rt = epoll_ctl(m_epfd, op, fd, &epevent);
        if(rt) {
            DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING(
                "epoll_ctl(", m_epfd, ", ",
                op, ", ",  fd, ", ", (EPOLL_EVENTS)epevent.events, "):",
                rt, " (", errno, ") (", strerror(errno), ") fd_ctx->events=",
                (EPOLL_EVENTS)fd_ctx->events
            ));
            return -1;
        }

        //增加一个待处理事件
        ++m_pendingEventCount;
        fd_ctx->events = (Event)(fd_ctx->events | event);
        FdContext::EventContext& event_ctx = fd_ctx->getContext(event);
        //因为是add方法，所以这几个都该为空
        DW_ASSERT(!event_ctx.scheduler
                    && !event_ctx.fiber
                    && !event_ctx.cb);

        event_ctx.scheduler = Scheduler::GetThis();
        if(cb) {
            event_ctx.cb.swap(cb);
        } else {
            //这里还是要留个心眼
            event_ctx.fiber = Fiber::GetThis();
            DW_ASSERT(event_ctx.fiber->getState() == Fiber::EXEC,
                        TOSTRING("state=", event_ctx.fiber->getState()));
        }
        return 0;
    }

    bool IOManager::delEvent(int fd, Event event) {
        RWMutexType::ReadLock lock(m_mutex);
        if((int)m_fdContexts.size() <= fd) {
            return false;
        }
        FdContext* fd_ctx = m_fdContexts[fd];
        lock.unlock();

        FdContext::MutexType::Lock lock2(fd_ctx->mutex);
        if(!(fd_ctx->events & event)) {
            return false;
        }

        Event new_events = (Event)(fd_ctx->events & ~event);
        int op = new_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        epoll_event epevent;
        epevent.events = EPOLLET | new_events;
        epevent.data.ptr = fd_ctx;

        int rt = epoll_ctl(m_epfd, op, fd, &epevent);
        if(rt) {
            DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING(
                "epoll_ctl(", m_epfd, ", ",
                op, ", ",  fd, ", ", (EPOLL_EVENTS)epevent.events, "):",
                rt, " (", errno, ") (", strerror(errno), ") fd_ctx->events=",
                (EPOLL_EVENTS)fd_ctx->events
            ));
            return false;
        }

        --m_pendingEventCount;
        fd_ctx->events = new_events;
        FdContext::EventContext& event_ctx = fd_ctx->getContext(event);
        //将已经删除的事件 清空
        fd_ctx->resetContext(event_ctx);
        return true;
    }

    bool IOManager::cancelEvent(int fd, Event event) {
        RWMutexType::ReadLock lock(m_mutex);
        if((int)m_fdContexts.size() <= fd) {
            return false;
        }
        FdContext* fd_ctx = m_fdContexts[fd];
        lock.unlock();

        FdContext::MutexType::Lock lock2(fd_ctx->mutex);
        if(!(fd_ctx->events & event)) {
            return false;
        }

        Event new_events = (Event)(fd_ctx->events & ~event);
        int op = new_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
        epoll_event epevent;
        epevent.events = EPOLLET | new_events;
        epevent.data.ptr = fd_ctx;

        int rt = epoll_ctl(m_epfd, op, fd, &epevent);
        if(rt) {
            DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING(
                "epoll_ctl(", m_epfd, ", ",
                op, ", ",  fd, ", ", (EPOLL_EVENTS)epevent.events, "):",
                rt, " (", errno, ") (", strerror(errno), ") fd_ctx->events=",
                (EPOLL_EVENTS)fd_ctx->events
            ));
            return false;
        }

        //触发一次
        fd_ctx->triggerEvent(event);
        --m_pendingEventCount;
        return true;
    }

    bool IOManager::cancelAll(int fd) {
        RWMutexType::ReadLock lock(m_mutex);
        if((int)m_fdContexts.size() <= fd) {
            return false;
        }
        FdContext* fd_ctx = m_fdContexts[fd];
        lock.unlock();

        FdContext::MutexType::Lock lock2(fd_ctx->mutex);
        if(!fd_ctx->events) {
            return false;
        }

        int op = EPOLL_CTL_DEL;
        epoll_event epevent;
        epevent.events = 0;
        epevent.data.ptr = fd_ctx;

        int rt = epoll_ctl(m_epfd, op, fd, &epevent);
        if(rt) {
            DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING(
                "epoll_ctl(", m_epfd, ", ",
                op, ", ",  fd, ", ", (EPOLL_EVENTS)epevent.events, "):",
                rt, " (", errno, ") (", strerror(errno), ") fd_ctx->events=",
                (EPOLL_EVENTS)fd_ctx->events
            ));
            return false;
        }

        if(fd_ctx->events & READ) {
            fd_ctx->triggerEvent(READ);
            --m_pendingEventCount;
        }
        if(fd_ctx->events & WRITE) {
            fd_ctx->triggerEvent(WRITE);
            --m_pendingEventCount;
        }

        DW_ASSERT(fd_ctx->events == 0);

        // delete fd_ctx;
        // m_fdContexts[fd] = new FdContext;
        // m_fdContexts[fd]->fd = fd; 
        // DW_ASSERT(m_fdContexts[fd]->events == 0);

        return true;
    }

    IOManager* IOManager::GetThis() {
        return dynamic_cast<IOManager*>(Scheduler::GetThis());
    }

    void IOManager::tickle() {
        if(!hasIdleThreads()) {
            return;
        }
        //通过一次写事件唤醒一下epoll
        int rt = write(m_tickleFds[1], "T", 1);
        DW_ASSERT(rt == 1);
    }

    bool IOManager::stopping() {
        uint64_t timeout = 0;
        return stopping(timeout);
        //return Scheduler::stopping() && m_pendingEventCount == 0;
    }

    void IOManager::idle() {
        DW_LOG_DEBUG((g_logger), __FILE__, __LINE__, "idle");
        const uint64_t MAX_EVNETS = 256;
        epoll_event* events = new epoll_event[MAX_EVNETS]();
        std::shared_ptr<epoll_event> shared_events(events, [](epoll_event* ptr){
            delete[] ptr;
        });

        while(true) {
            uint64_t next_timeout = 0;
            if(stopping(next_timeout)) {
                DW_LOG_INFO(g_logger, __FILE__, __LINE__, TOSTRING("name", getName(), " idle stopping exit"));
                break;
            }

            int rt = 0;
            do {
                static const int MAX_TIMEOUT = 3000;
                if(next_timeout != ~0ull) {
                    next_timeout = std::min(static_cast<int>(next_timeout), MAX_TIMEOUT);
                } else {
                    next_timeout = MAX_TIMEOUT;
                }
                //static const int MAX_TIMEOUT = 3000;
                rt = epoll_wait(m_epfd, events, MAX_EVNETS, static_cast<int>(next_timeout));
                if(rt < 0 && errno == EINTR) {
                } else {
                    break;
                }
            } while(true);

            std::vector<std::function<void()> > cbs;
            listExpiredCb(cbs);
            if(!cbs.empty()) {
                //SYLAR_LOG_DEBUG(g_logger) << "on timer cbs.size=" << cbs.size();
                schedule(cbs.begin(), cbs.end());
                cbs.clear();
            }

            //if(SYLAR_UNLIKELY(rt == MAX_EVNETS)) {
            //    SYLAR_LOG_INFO(g_logger) << "epoll wait events=" << rt;
            //}

            for(int i = 0; i < rt; ++i) {
                epoll_event& event = events[i];
                //因tickle而唤醒
                if(event.data.fd == m_tickleFds[0]) {
                    uint8_t dummy[256];
                    while(read(m_tickleFds[0], dummy, sizeof(dummy)) > 0);
                    continue;
                }

                FdContext* fd_ctx = (FdContext*)event.data.ptr;
                FdContext::MutexType::Lock lock(fd_ctx->mutex);
                if(event.events & (EPOLLERR | EPOLLHUP)) {
                    //获取fd_ctx的events
                    event.events |= (EPOLLIN | EPOLLOUT) & fd_ctx->events;
                }
                int real_events = NONE;
                //触发的事件作对比
                if(event.events & EPOLLIN) {
                    real_events |= READ;
                }
                if(event.events & EPOLLOUT) {
                    real_events |= WRITE;
                }

                if((fd_ctx->events & real_events) == NONE) {
                    continue;
                }

                //把触发过的事件抹去
                int left_events = (fd_ctx->events & ~real_events);
                int op = left_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
                event.events = EPOLLET | left_events;

                int rt2 = epoll_ctl(m_epfd, op, fd_ctx->fd, &event);
                if(rt2) {
                    DW_LOG_ERROR(g_logger, __FILE__, __LINE__, TOSTRING(
                        "epoll_ctl(", m_epfd, ", ",
                        op, ", ",  fd_ctx->fd, ", ", (EPOLL_EVENTS)event.events, "):",
                        rt, " (", errno, ") (", strerror(errno), ") fd_ctx->events=",
                        (EPOLL_EVENTS)fd_ctx->events
                    ));
                    continue;
                }

                //SYLAR_LOG_INFO(g_logger) << " fd=" << fd_ctx->fd << " events=" << fd_ctx->events
                //                         << " real_events=" << real_events;
                //根据对应事件触发事件
                if(real_events & READ) {
                    fd_ctx->triggerEvent(READ);
                    --m_pendingEventCount;
                }
                if(real_events & WRITE) {
                    fd_ctx->triggerEvent(WRITE);
                    --m_pendingEventCount;
                }
            }

            // Fiber::ptr cur = Fiber::GetThis();
            // auto raw_ptr = cur.get();
            // cur.reset();

            // raw_ptr->swapOut();
            // DW_LOG_INFO(g_logger, __FILE__, __LINE__, "back to main");
            Fiber::YieldToHold();
            // DW_LOG_INFO(g_logger, __FILE__, __LINE__, "back to idle");
        }
    }

    bool IOManager::stopping(uint64_t& timeout) {
        timeout = getNextTimer();
        return timeout == ~0ull
            && m_pendingEventCount == 0
            && Scheduler::stopping();

    }

    void IOManager::onTimerInsertedAtFront() {
        tickle();
    }

}