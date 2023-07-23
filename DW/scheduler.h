#pragma once 

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include "fiber.h"
#include "thread.h"
#include "mutex.h"

namespace DW {
    class Scheduler {
    public:
        using ptr = std::shared_ptr<Scheduler>;
        using MutexType = Mutex;

        Scheduler(size_t threads = 1, const std::string& name = "");
        virtual ~Scheduler();

        const std::string& getName() const { return m_name;}

        static Scheduler* GetThis();

        static Fiber* GetMainFiber();

        void start();

        void stop();

        //这里是要写内存所以要加锁
        template<class FiberOrCb>
        void schedule(FiberOrCb fc, int thread = -1) {
            bool need_tickle = false;
            {
                MutexType::Lock lock(m_mutex);
                need_tickle = scheduleNoLock(fc, thread);
            }

            if(need_tickle) {
                tickle();
            }
        }

        template<class InputIterator>
        void schedule(InputIterator begin, InputIterator end) {
            bool need_tickle = false;
            {
                MutexType::Lock lock(m_mutex);
                while(begin != end) {
                    need_tickle = scheduleNoLock(&*begin, -1) || need_tickle;
                    ++begin;
                }
            }
            if(need_tickle) {
                tickle();
            }
        }
    protected:
        virtual void tickle();

        void run();

        virtual bool stopping();

        virtual void idle();

        void setThis();

        bool hasIdleThreads() { return m_idleThreadCount > 0;}
    private:
        template<class FiberOrCb>
        bool scheduleNoLock(FiberOrCb fc, int thread) {
            bool need_tickle = m_fibers.empty();
            FiberAndThread ft(fc, thread);
            if(ft.fiber || ft.cb) {
                m_fibers.push_back(ft);
            }
            return need_tickle;
        }
    private:
        struct FiberAndThread {
            /// 协程
            Fiber::ptr fiber;
            /// 协程执行函数
            std::function<void()> cb;
            /// 线程id
            int thread;

            FiberAndThread(Fiber::ptr f, int thr)
                :fiber(f), thread(thr) {
            }

            FiberAndThread(Fiber::ptr* f, int thr)
                :thread(thr) {
                fiber.swap(*f);
            }

            FiberAndThread(std::function<void()> f, int thr)
                :cb(f), thread(thr) {
            }

            FiberAndThread(std::function<void()>* f, int thr)
                :thread(thr) {
                cb.swap(*f);
            }

            FiberAndThread()
                :thread(-1) {
            }

            void reset() {
                fiber = nullptr;
                cb = nullptr;
                thread = -1;
            }
        };
    private:
        /// Mutex
        MutexType m_mutex;
        /// 线程池
        std::vector<Thread::ptr> m_threads;
        /// 待执行的协程队列
        std::list<FiberAndThread> m_fibers;
        /// use_caller为true时有效, 调度协程
        Fiber::ptr m_rootFiber;
        /// 协程调度器名称
        std::string m_name;
    protected:
        /// 协程下的线程id数组
        std::vector<int> m_threadIds;
        /// 线程数量
        size_t m_threadCount = 0;
        /// 工作线程数量
        std::atomic<size_t> m_activeThreadCount = {0};
        /// 空闲线程数量
        std::atomic<size_t> m_idleThreadCount = {0};
        /// 是否正在停止
        bool m_stopping = true;
        /// 是否自动停止
        bool m_autoStop = false;
        /// 主线程id(use_caller)
        int m_rootThread = 0;
    };
}
