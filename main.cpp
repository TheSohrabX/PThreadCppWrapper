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

void
worker3(int num1, int num2, int num3)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "this is the first number:" << num1;
    qDebug() << "this is the second number:" << num2;
    qDebug() << "this is the third number:" << num3;
}

int
main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    pthread_t        thread;
    // TestClass        testClass;
    // std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    // worker2Caller();
    // testClass.runWorker1();
    // testClass.runWorker2();
    // testClass.runWorker2_2();
    // testClass.runWorker2_3(numbers);

    // PThreadCppWrapper::run(thread, &testClass, &TestClass::worker2, numbers);

    // auto             lambdaFunction = [](int a, std::string b) {
    //     qDebug() << "hi";
    //     qDebug() << "this is sohrabs wrapper for p_fucking_thread.";
    //     qDebug() << "this is the first argument:" << a;
    //     qDebug() << "this is the second argument:" << b;
    // };

    // PThreadCppWrapper::run(thread, lambdaFunction, 123, std::string("the string"));
    PThreadCppWrapper::run(thread, &worker3, 123, 456, 789);

    return a.exec();
}
