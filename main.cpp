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
