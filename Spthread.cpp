#include "Spthread.h"

Spthread::Thread::Thread() {}

Spthread::Thread::~Thread()
{
    _pthread_cleanup_dest(m_thread);
}

void
Spthread::Thread::start()
{
    Spthread::run(m_thread, this, &Thread::run);
}

