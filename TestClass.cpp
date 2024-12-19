#include "TestClass.h"

#include <QDebug>

TestClass::TestClass(QObject *parent) :
    QObject {parent}
{}

qint64
TestClass::worker1()
{
    qDebug() << Q_FUNC_INFO << "Invoked";

    if(m_numbers.empty()) return 0;

    return std::accumulate(m_numbers.begin(), m_numbers.end(), 1, std::multiplies<qint64>());
}

qint64
TestClass::worker2(const std::vector<int> &numbers)
{
    qDebug() << Q_FUNC_INFO << "Invoked";

    if(numbers.empty()) return 0;

    return std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<qint64>());
}

void
TestClass::runWorker1()
{
    PThreadCppWrapper::run(m_thread, this, &TestClass::worker1);
}

void
TestClass::runWorker2()
{
    PThreadCppWrapper::run(m_thread, this, &TestClass::worker2, m_numbers);
}
