#include "TestClass.h"

#include "PThreadCppWrapper.h"

TestClass::TestClass(QObject *parent) :
    QObject {parent}
{}

qint64
TestClass::worker1()
{
    if(m_numbers.empty()) return 0;

    return std::accumulate(m_numbers.begin(), m_numbers.end(), 1, std::multiplies<qint64>());
}

qint64
TestClass::worker2(const std::vector<int> &numbers)
{
    if(numbers.empty()) return 0;

    return std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<qint64>());
}

void
TestClass::runWorker1()
{
    PThreadBySohrab::run(m_thread, this, &TestClass::worker1);
}
