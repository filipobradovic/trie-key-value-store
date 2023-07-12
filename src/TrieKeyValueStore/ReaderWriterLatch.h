#pragma once

#include <shared_mutex>

class ReaderWriterLatch {

public:
    void w_lock();
    void w_unlock();
    void r_lock();
    void r_unlock();

private:
    std::shared_mutex m_mutex;
};
