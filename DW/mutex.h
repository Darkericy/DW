#pragma once

#include <semaphore.h>
#include <unistd.h>
#include <stdexcept>
#include <atomic>

#include "noncopyable.h"

namespace DW{
    //信号量
    class Semaphore: Noncopyable{
    public:
        Semaphore(const Semaphore&) = delete;
        Semaphore(Semaphore&&) = delete;
        Semaphore& operator==(const Semaphore&) = delete;

        Semaphore();
        Semaphore(uint32_t count);
        ~Semaphore();

        void wait();
        void notify();

    private:
        sem_t m_semaphore;
    };

    //互斥锁资源管理类
    template<class T>
    struct ScopedLockImpl{
    public:

        ScopedLockImpl(T& mutex): m_mutex(mutex){
            m_mutex.lock();
            m_locked = true;
        }   
        ~ScopedLockImpl(){
            unlock();
        }

        void lock(){
            if(!m_locked){
                m_mutex.lock();
                m_locked = true;
            }
        }

        void unlock(){
            if(m_locked){
                m_mutex.unlock();
                m_locked = false;
            }
        }

    private:
        T& m_mutex;
        bool m_locked;
    };

    template<class T>
    struct ReadScopedLockImpl {
    public:
        ReadScopedLockImpl(T& mutex)
            :m_mutex(mutex) {
            m_mutex.rdlock();
            m_locked = true;
        }
        ~ReadScopedLockImpl() {
            unlock();
        }

        void lock() {
            if(!m_locked) {
                m_mutex.rdlock();
                m_locked = true;
            }
        }

        void unlock() {
            if(m_locked) {
                m_mutex.unlock();
                m_locked = false;
            }
        }
    private:
        T& m_mutex;
        bool m_locked;
    };

    template<class T>
    struct WriteScopedLockImpl {
    public:
        WriteScopedLockImpl(T& mutex)
            :m_mutex(mutex) {
            m_mutex.wrlock();
            m_locked = true;
        }
        ~WriteScopedLockImpl() {
            unlock();
        }

        void lock() {
            if(!m_locked) {
                m_mutex.wrlock();
                m_locked = true;
            }
        }

        void unlock() {
            if(m_locked) {
                m_mutex.unlock();
                m_locked = false;
            }
        }
    private:
        T& m_mutex;
        bool m_locked;
    };

    class NullMutex: Noncopyable {
    public:
        using Lock = ScopedLockImpl<NullMutex>;

        NullMutex() {}

        ~NullMutex() {}

        void lock() {}

        void unlock() {}
    };

    class NullRWMutex: Noncopyable {
    public:
        using ReadLock = ReadScopedLockImpl<NullRWMutex>;
        using WriteLock = WriteScopedLockImpl<NullRWMutex>; 

        NullRWMutex() {}

        ~NullRWMutex() {}

        void rdlock() {}
        void wrlock() {}

        void unlock() {}
    };

    class Spinlock: Noncopyable {
    public:
        /// 局部锁
        using Lock = ScopedLockImpl<Spinlock>;

        Spinlock() {
            pthread_spin_init(&m_mutex, 0);
        }

        ~Spinlock() {
            pthread_spin_destroy(&m_mutex);
        }

        void lock() {
            pthread_spin_lock(&m_mutex);
        }

        void unlock() {
            pthread_spin_unlock(&m_mutex);
        }
    private:
        /// 自旋锁
        pthread_spinlock_t m_mutex;
    };

    class CASLock: Noncopyable  {
    public:
        using Lock = ScopedLockImpl<CASLock>;

        CASLock() {
            m_mutex.clear();
        }

        ~CASLock() {
        }

        /**
         * @brief 上锁
         */
        void lock() {
            while(std::atomic_flag_test_and_set_explicit(&m_mutex, std::memory_order_acquire));
        }

        /**
         * @brief 解锁
         */
        void unlock() {
            std::atomic_flag_clear_explicit(&m_mutex, std::memory_order_release);
        }
    private:
        /// 原子状态
        volatile std::atomic_flag m_mutex;
    };

    class Mutex: Noncopyable{
    public: 
        using Lock = ScopedLockImpl<Mutex>;

        Mutex() {
            pthread_mutex_init(&m_mutex, nullptr);
        }

        ~Mutex() {
            pthread_mutex_destroy(&m_mutex);
        }

        void lock() {
            pthread_mutex_lock(&m_mutex);
        }

        void unlock() {
            pthread_mutex_unlock(&m_mutex);
        }
    private:
        pthread_mutex_t m_mutex;
    };

    class RWMutex: Noncopyable{
    public:
        using ReadLock = ReadScopedLockImpl<RWMutex>;
        using WriteLock = WriteScopedLockImpl<RWMutex>; 

        RWMutex(){
            pthread_rwlock_init(&m_lock, nullptr);
        }
        ~RWMutex(){
            pthread_rwlock_destroy(&m_lock);
        }

        void rdlock() {
            pthread_rwlock_rdlock(&m_lock);
        }

        void wrlock() {
            pthread_rwlock_wrlock(&m_lock);
        }

        void unlock() {
            pthread_rwlock_unlock(&m_lock);
        }

    private:
        pthread_rwlock_t m_lock;
    };
}