#ifndef VALREADER_H
#define VALREADER_H

#include <QObject>
#include <QDebug>
#include <QPoint>

#include "mythread.h"

class valReader : public QObject
{
    Q_OBJECT
public:
    explicit valReader(QObject *parent = nullptr);

    Q_INVOKABLE void startThread();
    Q_INVOKABLE void stopThread();
    Q_INVOKABLE void test();
    Q_INVOKABLE double read_sensor();

    mythread mthread;
    double sensor_reading;
    bool isRunning;


signals:

public slots:


};

#endif // VALREADER_H
