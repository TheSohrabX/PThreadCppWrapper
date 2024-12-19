#include "TestClass.h"

#include <QCoreApplication>

void
worker2Caller()
{
    pthread_t        thread;
    TestClass       *testClassInstance = new TestClass;
    std::vector<int> numbers           = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    PThreadCppWrapper::run(thread, testClassInstance, &TestClass::worker2, numbers);
}


int
main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestClass        testClass;
    // pthread_t        thread;
    std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    // PThreadCppWrapper::run(thread, &testClass, &TestClass::worker2, numbers);

    // worker2Caller();
    // testClass.runWorker1();

    return a.exec();
}
