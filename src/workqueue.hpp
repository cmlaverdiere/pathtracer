#ifndef WORKQUEUE_H
#define WORKQUEUE_H

#include <deque>
#include <thread>
#include <mutex>

/* A simple thread-safe queue for integer operations. */
class WorkQueue {
    private:
        std::mutex m_mutex;
        std::deque<int> m_queue;

    public:
        WorkQueue() {};
        void push_back(int n);
        int pop_front();
        int size();
};

#endif
