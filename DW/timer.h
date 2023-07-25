#pragma once

#include <memory>
#include <vector>
#include <set>
#include "thread.h"

namespace DW {

    class TimerManager;
    //@brief 定时器
    //Timer的出现和TimerManager的出现绑定了，所以有关Timer的写读操作都使用TimerManager的锁
    //这里我并不愿意更改使这两个类耦合度降低，因为每一个Timer类都应该归属于一个TimerManager，为了减少一定的管理开销，将他们绑定在一起更方便我们操作。
    class Timer : public std::enable_shared_from_this<Timer> {
    friend class TimerManager;
    public:
        /// 定时器的智能指针类型
        using ptr = std::shared_ptr<Timer>;

        //取消定时器
        bool cancel();

        //重新设置时间
        bool refresh();

        //重置定时器时间
        bool reset(uint64_t ms, bool from_now);
    private:
        /**
         * @brief 构造函数
         * @param[in] ms 定时器执行间隔时间
         * @param[in] cb 回调函数
         * @param[in] recurring 是否循环
         * @param[in] manager 定时器管理器
         */
        Timer(uint64_t ms, std::function<void()> cb,
            bool recurring, TimerManager* manager);
    private:
        /// 是否循环定时器
        bool m_recurring = false;
        /// 执行周期
        uint64_t m_ms = 0;
        /// 精确的执行时间
        uint64_t m_next = 0;
        /// 回调函数
        std::function<void()> m_cb;
        /// 定时器管理器
        TimerManager* m_manager = nullptr;
    private:

        struct Comparator {
            bool operator()(const Timer::ptr& lhs, const Timer::ptr& rhs) const;
        };


        //这个构造函数就是为了二分查找存在的，我给他放到private里
        Timer(uint64_t next);
    };

    //定时器管理器
    class TimerManager {
    friend class Timer;
    public:
        /// 读写锁类型
        using RWMutexType = RWMutex;

        TimerManager();

        virtual ~TimerManager();

        Timer::ptr addTimer(uint64_t ms, std::function<void()> cb
                            ,bool recurring = false);

        //weak_ptr是条件，这是我从未接触过的新东西，太新颖了我天
        Timer::ptr addConditionTimer(uint64_t ms, std::function<void()> cb
                            ,std::weak_ptr<void> weak_cond
                            ,bool recurring = false);

        //到最近一个定时器执行的时间间隔(毫秒)
        uint64_t getNextTimer();

        //获取需要执行的定时器的回调函数列表
        void listExpiredCb(std::vector<std::function<void()> >& cbs);

        bool hasTimer();
    protected:

        //当有新的定时器插入到定时器的首部,执行该函数
        virtual void onTimerInsertedAtFront() = 0;

        //将定时器添加到管理器中
        void addTimer(Timer::ptr val, RWMutexType::WriteLock& lock);
    private:
        //检测服务器时间是否被调后了
        bool detectClockRollover(uint64_t now_ms);
    private:
        /// Mutex
        RWMutexType m_mutex;
        /// 定时器集合
        std::set<Timer::ptr, Timer::Comparator> m_timers;
        /// 是否触发onTimerInsertedAtFront
        bool m_tickled = false;
        /// 上次执行时间
        uint64_t m_previouseTime = 0;
    };

}