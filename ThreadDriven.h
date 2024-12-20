#ifndef THREADDRIVEN_H
#define THREADDRIVEN_H

#include "./Spthread.h"

class ThreadDriven : public Spthread::Thread
{
public:
    ThreadDriven();

protected:
    void run() override;

private:
    void heavyTask();
};

#endif    // THREADDRIVEN_H
