#pragma once 

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include <semaphore.h>

namespace DW{
    class Semaphore{
    public:
        Semaphore(const Semaphore&) = delete;
        Semaphore(Semaphore&&) = delete;
        Semaphore& operator==(const Semaphore&) = delete;

        Semaphore()
        Semaphore(uint32_t count);
        ~Semaphore();

        void wait();
        void notify();

    private:
        sem_t m_semaphore;
    }

    class Thread{
    public:
        using ptr = std::shared_ptr<Thread>;

        Thread(const Thread&) = delete;
        Thread(Thread&&) = delete;
        Thread& operator==(const Thread&) = delete;

        Thread(std::function<void()> cb, const std::string& name);
        ~Thread();

        pid_t getId() const { return m_id; };
        const std::string& getName() const { return m_name; };
        void join();
        
        static Thread* GetThis();
        static const std::string& GetName();
        static void SetName(const std::string& name);

    private:
        pid_t m_id = -1;
        pthread_t m_thread = 0;
        std::function<void()> m_cb;
        std::string m_name;

        static void* run(void *arg);
    };
};