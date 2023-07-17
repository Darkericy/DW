#pragma once

#include <semaphore.h>
#include <unistd.h>
#include <stdexcept>

namespace DW{
    //信号量
    class Semaphore{
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

    class RWMutex{
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