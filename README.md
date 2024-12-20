# Spthread: A C++ Wrapper for pthread

this tool is a thin c++ wrapper for pthrad functions.

i'm working on it to cover more pthread funcions for better integrity with C++.

till now, i only added support for pthread_create.

## Note:
i used Qt for making this project but the wrapper DOES NOT HAVE any dependency on Qt framework.

# Examples:

## 1. Running Lambda Functions:

```CPP
pthread_t thread;

auto lambdaFunction = [](int number, std::string string) {
  qDebug() << "hi";
  qDebug() << "this is a c++ wrapper for p_fucking_thread.";
  qDebug() << "this is the first argument:" << number;
  qDebug() << "this is the second argument:" << string;
};

Spthread::run(thread, lambdaFunction, 123, std::string("the string"));
```

---- OR
```CPP
auto lambdaFunction = [](int number, std::string string) {
  qDebug() << "hi";
  qDebug() << "this is a c++ wrapper for p_fucking_thread.";
  qDebug() << "this is the first argument:" << number;
  qDebug() << "this is the second argument:" << string;
};

Spthread::singleShot(lambdaFunction, 123, std::string("the string"));
```



## 2. Running Functions:
```CPP
void
worker(int num1, int num2, int num3)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "this is the first number:" << num1;
    qDebug() << "this is the second number:" << num2;
    qDebug() << "this is the third number:" << num3;
}
```
```CPP
int
main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pthread_t thread;
    Spthread::run(thread, &worker, 123, 456, 789);

    return a.exec();
}
```
---- OR
```CPP
int
main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Spthread::singleShot(&worker, 123, 456, 789);

    return a.exec();
}
```


## 3. Running Member Funcions:
Consider that we have a class like this:

```CPP
class HeavyTasks
{

public:    // CTORS
    HeavyTasks()  = default;
    ~HeavyTasks() = default;

public:    // function members
    void
    heavyTask1()
    {
        qDebug() << Q_FUNC_INFO;
        qDebug() << "this is the first heavy task.";
        qDebug() << std::accumulate(m_numbers.begin(), m_numbers.end(), 1, std::multiplies<int64_t>());
    }

    void
    heavyTask2(std::vector<int> numbers)
    {
        qDebug() << Q_FUNC_INFO;
        qDebug() << "this is the second heavy task.";
        qDebug() << std::accumulate(numbers.begin(), numbers.end(), 0, std::plus<int64_t>());
    }

private:    // data members
    std::vector<int> m_numbers  = {1, 2, 3, 4, 5, 6, 7, 8, 9};
};
```

now we want to run heavyTask1 and heavyTask2 with pthread.
1. running heavyTask1
```CPP
HeavyTasks heavyTasks;
Spthread::singleShot(&heavyTasks, &HeavyTasks::heavyTask1);
```
---- OR
```CPP
pthread_t thread;
HeavyTasks heavyTasks;
Spthread::run(thread, &heavyTasks, &HeavyTasks::heavyTask1);
```
2. running heavyTask2
```CPP
HeavyTasks heavyTasks;
std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};
Spthread::singleShot(&heavyTasks, &HeavyTasks::heavyTask2, numbers);
```
---- OR
```CPP
pthread_t thread;
HeavyTasks heavyTasks;
std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70, 80, 90};
Spthread::run(thread, &heavyTasks, &HeavyTasks::heavyTask2, numbers);
```

## 4. Running Member Function (from within):
Consider that we have a class like this:
----HeavyTasks.h
```CPP
class HeavyTasks
{

public:    // CTORS
    HeavyTasks()  = default;
    ~HeavyTasks() = default;

public:
    void
    run()
    {
        Spthread::singleShot(this, &HeavyTasks::heavyTask);
----or
        Spthread::run(m_pthread, this, &HeavyTasks::heavyTask);
    }


private:    // function members
    void
    heavyTask()
    {
        qDebug() << Q_FUNC_INFO;
        qDebug() << "this is the first heavy task.";
        qDebug() << std::accumulate(m_numbers.begin(), m_numbers.end(), 1,
                                    std::multiplies<int64_t>());
        ;
    }

private:    // data members
    std::vector<int> m_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    pthread_t        m_pthread;
};
```
----main.cpp
```CPP
int
main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HeavyTasks       htInstance;
    htInstance.run();

    return a.exec();
}
```


## 5. Using Spthread::Thread as base class (Like QThread):
----ThreadDriven.h
```CPP
#pragma once

#include "Spthread.h"

class ThreadDriven : public Spthread::Thread
{
public:
    ThreadDriven();

protected:
    void run() override;

private:
    void heavyTask();
};

```
----ThreadDriven.cpp
```cPP
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

```
----main.cpp
```CPP
#include "./ThreadDriven.h"

#include <QCoreApplication>


int
main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ThreadDriven     thread;
    thread.start();

    return a.exec();
}
```


















