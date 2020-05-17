#include "valreader.h"



valReader::valReader(QObject *parent) : QObject(parent)
{
    sensor_reading=2;
    isRunning = false;
}

void valReader::test()
{

    //qDebug() << mthread.sensor_val;

}

void valReader::startThread()
{

    qDebug() << "here1 \n";
    mthread.start();
    qDebug() << "here2 \n";

}

void valReader::stopThread()
{

    isRunning = false;
    mthread.stop_thread();

}

double valReader::read_sensor()
{

    //sensor_reading = counter;
    return mthread.get_val();

}

