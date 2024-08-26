/*
    threadworker.h

    Class declaration for ThreadWorker.
*/

#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>

/*
    ThreadWorker

    This is the object used to run actions in a separate thread. It gets moved to another thread, and you can give it
    jobs to run on that thread using QMetaObject::invokeMethod(). See tetrooscontroller.cpp for examples.
*/
class ThreadWorker : public QObject
{
    Q_OBJECT

public slots:
    void executeTask(std::function<void()> task)
    {
        task();
    }
};

#endif // THREADWORKER_H
