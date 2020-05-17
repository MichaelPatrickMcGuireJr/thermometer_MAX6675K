#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <iostream>
#include <QThread>
#include <QMutex>

#include "read_max6675k.h"


class mythread : public QThread
{
public:
    explicit mythread();

    void run();
    void stop_thread();
    double get_val();

    read_max6675k read_max;

    double sensor_val;

private:

    QMutex mutex;

    double receivedData;
    bool is_running;

};

#endif // MYTHREAD_H
