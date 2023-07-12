#include "ReaderWriterLatch.h"

void ReaderWriterLatch::w_lock()
{
    m_mutex.lock();
}

void ReaderWriterLatch::w_unlock()
{
    m_mutex.unlock();
}

void ReaderWriterLatch::r_lock()
{
    m_mutex.lock_shared();
}

void ReaderWriterLatch::r_unlock()
{
    m_mutex.unlock_shared();
}
