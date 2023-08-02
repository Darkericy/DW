#include "scheduler.h"
#include "log.h"
#include "macro.h"
#include "fiber.h"
#include "hook.h"

namespace DW {

    static DW::Logger::ptr g_logger = DW_LOG_NAME("system");

    static thread_local Scheduler* t_scheduler = nullptr;       //当前调度器
    static thread_local Fiber* t_scheduler_fiber = nullptr;     //当前线程的主携程

    Scheduler::Scheduler(size_t threads, const std::string& name)
        :m_name(name) {
        DW_ASSERT(threads > 0);

        // if(use_caller) {
        //     DW::Fiber::GetThis();
        //     --threads;

        //     DW_ASSERT(GetThis() == nullptr);
        //     //t_scheduler = this;

        //     //即使是主携程，也是该线程中的第二个携程
        //     m_rootFiber = std::make_shared<Fiber>(std::bind(&Scheduler::run, this), 0);
        //     DW::Thread::SetName(m_name);

        //     //t_scheduler_fiber = m_rootFiber.get();
        //     t_scheduler_fiber = Fiber::GetThis().get();
        //     m_rootThread = DW::GetThreadId();
        //     m_threadIds.push_back(m_rootThread);
        // } else {
        //     m_rootThread = -1;
        // }
        m_rootThread = -1;
        t_scheduler = this;
        m_threadCount = threads;
    }

    Scheduler::~Scheduler() {
        DW_ASSERT(m_stopping);
        if(GetThis() == this) {
            t_scheduler = nullptr;
        }
    }

    //拿到当前携程调度的指针
    Scheduler* Scheduler::GetThis() {
        return t_scheduler;
    }

    Fiber* Scheduler::GetMainFiber() {
        return t_scheduler_fiber;
    }

    void Scheduler::start() {
        MutexType::Lock lock(m_mutex);
        if(!m_stopping) {
            return;
        }
        m_stopping = false;
        DW_ASSERT(m_threads.empty());

        m_threads.resize(m_threadCount);
        //创建线程池  线程都跑在run方法上
        for(size_t i = 0; i < m_threadCount; ++i) {
            m_threads[i].reset(new Thread(std::bind(&Scheduler::run, this)
                                , m_name + "_" + std::to_string(i)));
            m_threadIds.push_back(m_threads[i]->getId());
        }
        //lock.unlock();

        // if(m_rootFiber) {
        //    m_rootFiber->swapIn();
        //    //m_rootFiber->call();
        //    DW_LOG_INFO(g_logger, __FILE__, __LINE__, TOSTRING("swapOut ", m_rootFiber->getState()));
        // }
    }

    void Scheduler::stop() {
        m_autoStop = true;
        if(m_rootFiber
                && m_threadCount == 0
                && (m_rootFiber->getState() == Fiber::TERM
                    || m_rootFiber->getState() == Fiber::INIT)) {
            
            DW_LOG_INFO(g_logger, __FILE__, __LINE__, TOSTRING(this, "stopped"));
            m_stopping = true;

            if(stopping()) {
                return;
            }
        }

        //bool exit_on_this_fiber = false;
        // if(m_rootThread != -1) {
        //     DW_ASSERT(GetThis() == this);
        // } else {
        //     DW_ASSERT(GetThis() != this);
        // }

        m_stopping = true;
        for(size_t i = 0; i < m_threadCount; ++i) {
            tickle();
        }

        if(m_rootFiber) {
            tickle();
        }

        if(m_rootFiber) {
            //while(!stopping()) {
            //    if(m_rootFiber->getState() == Fiber::TERM
            //            || m_rootFiber->getState() == Fiber::EXCEPT) {
            //        m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, true));
            //        SYLAR_LOG_INFO(g_logger) << " root fiber is term, reset";
            //        t_fiber = m_rootFiber.get();
            //    }
            //    m_rootFiber->call();
            //}
            if(!stopping()) {
                m_rootFiber->swapIn();
            }
        }

        std::vector<Thread::ptr> thrs;
        {
            MutexType::Lock lock(m_mutex);
            thrs.swap(m_threads);
        }

        DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("stop and wait"));

        //关闭线程池
        //我以前写的线程池都是将他们与主线程分离开，这里是将他们管理起来
        for(auto& i : thrs) {
            i->join();
        }
        //if(exit_on_this_fiber) {
        //}
    }

    void Scheduler::setThis() {
        t_scheduler = this;
    }

    void Scheduler::run() {
        DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING(m_name, " run"));
        set_hook_enable(true);
        setThis();
        if(static_cast<int>(DW::GetThreadId()) != m_rootThread) {
            //需要创建一个主携程
            t_scheduler_fiber = Fiber::GetThis().get();
        }

        Fiber::ptr idle_fiber(new Fiber(std::bind(&Scheduler::idle, this)));
        Fiber::ptr cb_fiber;

        FiberAndThread ft;
        while(true) {
            ft.reset();
            bool tickle_me = false;
            bool is_active = false;
            {
                MutexType::Lock lock(m_mutex);
                auto it = m_fibers.begin();
                while(it != m_fibers.end()) {
                    //需要其他线程来处理
                    if(it->thread != -1 && it->thread != static_cast<int>(DW::GetThreadId())) {
                        ++it;
                        tickle_me = true;
                        continue;
                    }

                    DW_ASSERT(it->fiber || it->cb); //断言判断当前调用的合法性
                    if(it->fiber && it->fiber->getState() == Fiber::EXEC) {
                        ++it;
                        continue;
                    }

                    ft = *it;
                    m_fibers.erase(it++);
                    ++m_activeThreadCount;
                    is_active = true;
                    break;
                }
                tickle_me = it != m_fibers.end();
            }

            if(tickle_me) {
                tickle();
            }

            if(ft.fiber && (ft.fiber->getState() != Fiber::TERM
                            && ft.fiber->getState() != Fiber::EXCEPT)) {
                DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("get mission id= ", GetThreadId()));
                ft.fiber->swapIn();
                --m_activeThreadCount;

                if(ft.fiber->getState() == Fiber::READY) {
                    schedule(ft.fiber);
                } else if(ft.fiber->getState() != Fiber::TERM
                        && ft.fiber->getState() != Fiber::EXCEPT) {
                    //ft.fiber->m_state = Fiber::HOLD;
                }
                ft.reset();
            } else if(ft.cb) {
                DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("get mission id= ", GetThreadId()));
                if(cb_fiber) {
                    cb_fiber->reset(ft.cb);
                } else {
                    cb_fiber.reset(new Fiber(ft.cb));
                }
                //DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("chengmo l wo"));
                ft.reset();
                cb_fiber->swapIn();
                --m_activeThreadCount;
                if(cb_fiber->getState() == Fiber::READY) {
                    DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, "ready");
                    schedule(cb_fiber);
                    cb_fiber.reset();
                } else if(cb_fiber->getState() == Fiber::EXCEPT
                        || cb_fiber->getState() == Fiber::TERM) {
                    DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, "nullptr");
                    cb_fiber->reset(nullptr);   //释放潜在资源
                } else {//if(cb_fiber->getState() != Fiber::TERM) {
                    //cb_fiber->m_state = Fiber::HOLD;
                    DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, "other");
                    cb_fiber.reset();
                }
            } else {
                if(is_active) {
                    --m_activeThreadCount;
                    continue;
                }
                if(idle_fiber->getState() == Fiber::TERM) {
                    DW_LOG_INFO(g_logger, __FILE__, __LINE__, "idle fiber term");
                    break;
                }

                ++m_idleThreadCount;
                idle_fiber->swapIn();
                //DW_LOG_DEBUG(g_logger, __FILE__, __LINE__, TOSTRING("back to run id= ", GetThreadId()));
                --m_idleThreadCount;
                if(idle_fiber->getState() != Fiber::TERM
                        && idle_fiber->getState() != Fiber::EXCEPT) {
                    //idle_fiber->m_state = Fiber::HOLD;
                }
            }
        }
    }

    void Scheduler::tickle() {
        DW_LOG_INFO(g_logger, __FILE__, __LINE__, "tickle");
    }

    bool Scheduler::stopping() {
        MutexType::Lock lock(m_mutex);
        return m_autoStop && m_stopping
            && m_fibers.empty() && m_activeThreadCount == 0;
    }

    void Scheduler::idle() {
        DW_LOG_INFO(g_logger, __FILE__, __LINE__, TOSTRING("idle"));
        while(!stopping()) {
            Fiber::YieldToHold();
        }
    }
}