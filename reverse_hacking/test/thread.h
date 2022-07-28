#pragma once


#include <thread>
#include <memory>
#include <functional>


class Thread
{
public:
    Thread() = default;
    virtual ~Thread()
    {
        join();
    }

    Thread(const Thread& rhs) = delete;
    Thread& operator=(const Thread& rhs) = delete;

    void threadStart()
    {
        //m_thread.reset(new std::thread(std::bind(&Thread::threadProc, this)));
        m_thread.reset(new std::thread([this]()
            {
                threadRun();
            }));
    }

    virtual void threadStop() {}

    void join()
    {
        if (m_thread->joinable())
        {
            m_thread->join();
        }
    }

protected:
    virtual void threadRun() = 0;

protected:
    bool m_stop{ false };
    std::shared_ptr<std::thread> m_thread;
};