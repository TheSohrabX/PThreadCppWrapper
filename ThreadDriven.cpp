#include "ThreadDriven.h"

#include <QDebug>

ThreadDriven::ThreadDriven() :
    Spthread::Thread()
{}

void
ThreadDriven::run()
{
    heavyTask();
}

void
ThreadDriven::heavyTask()
{
    qDebug() << Q_FUNC_INFO << " is running on thread: " << Spthread::Thread::currentThreadID();
}
