#include "TestClass.h"

TestClass::TestClass(QObject *parent) :
    QObject {parent}
{}

qint64
TestClass::worker1()
{
    if(m_numbers.empty()) return 0;

    return std::accumulate(m_numbers.begin(), m_numbers.end(), 1, std::multiplies<qint64>());
}
