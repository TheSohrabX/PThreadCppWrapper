#pragma once

#include <QObject>

class TestClass : public QObject
{
    Q_OBJECT

public:
    explicit TestClass(QObject *parent = nullptr);

    qint64 worker1();
    qint64 worker2(const std::vector<int> &numbers);

signals:

private:
    pthread_t        m_thread;
    std::vector<int> m_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

