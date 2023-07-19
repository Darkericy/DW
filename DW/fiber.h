#pragma once

#include <ucontext.h>
#include <memory>
#include <functional>

namespace DW{
    class Fiber : public std::enable_shared_from_this<Fiber> {
    public:
        using ptr = std::shared_ptr<Fiber>;

        enum State {
            /// 初始化状态
            INIT,
            /// 暂停状态
            HOLD,
            /// 执行中状态
            EXEC,
            /// 结束状态
            TERM,
            /// 可执行状态
            READY,
            /// 异常状态
            EXCEPT
        };
    private:
        //每个线程第一个构造的函数
        Fiber();

    public:
        Fiber(std::function<void()> cb, size_t stacksize = 0);

        ~Fiber();

        //重置函数，并重置状态
        void reset(std::function<void()> cb);

        //将当前协程切换到运行状态
        void swapIn();

        //将当前协程切换到后台
        void swapOut();

        State getState() const { return m_state;}

        uint64_t getId() const { return m_id;}
    public:

        //设置当前线程的运行协程
        static void SetThis(Fiber* f);

        //返回当前所在的协程
        static Fiber::ptr GetThis();

        //将当前协程切换到后台,并设置为READY状态
        static void YieldToReady();

        //@brief 将当前协程切换到后台,并设置为HOLD状态
        static void YieldToHold();

        static uint64_t TotalFibers();

        //协程执行函数
        static void MainFunc();

        static uint64_t GetFiberId();

    private:
        /// 协程id
        uint64_t m_id = 0;
        /// 协程运行栈大小
        uint32_t m_stacksize = 0;
        /// 协程状态
        State m_state = INIT;
        /// 协程上下文
        ucontext_t m_ctx;
        /// 协程运行栈指针
        void* m_stack = nullptr;
        /// 协程运行函数
        std::function<void()> m_cb;
    };
}