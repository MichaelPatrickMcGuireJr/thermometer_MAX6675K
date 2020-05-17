#include "mythread.h"

#include <iostream>
#include <unistd.h>

using namespace std;


mythread::mythread()
{

    read_max.init_sensor();
    receivedData = 0;
    is_running = false;

}


void mythread::run()
{
    is_running = true;
    while(is_running)
    {

        mutex.lock();
        receivedData = read_max.update_val();
        mutex.unlock();


        usleep(100000);

    }
}


void mythread::stop_thread()
{
    is_running=false;
}


double mythread::get_val()
{
    QString temp = "";

    if(is_running)
    {
        mutex.lock();
        sensor_val = receivedData;
        mutex.unlock();
    }
    else
    {
        temp = "-1";
    }
    return sensor_val;
}


