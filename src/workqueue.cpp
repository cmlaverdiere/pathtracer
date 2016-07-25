#include "workqueue.hpp"

void WorkQueue::push_back(int n)
{
    std::lock_guard<std::mutex> lock_g(m_mutex);
    m_queue.push_back(n);
}

int WorkQueue::pop_front()
{
    std::lock_guard<std::mutex> lock_g(m_mutex);
    int front = m_queue.front();
    m_queue.pop_front();
    return front;
}

int WorkQueue::size()
{
    std::lock_guard<std::mutex> lock_g(m_mutex);
    return m_queue.size();
}
