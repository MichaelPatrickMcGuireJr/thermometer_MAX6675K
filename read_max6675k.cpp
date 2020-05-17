#include "read_max6675k.h"


#define DBIT 13 // DO
#define CS 10   // CS
#define CLK 14  // CLK


#include <wiringPi.h>


// declare function
int Thermal_Couple_Read(void);

int SENSOR_VALUE = 0;
double Ctemp, Ftemp;

read_max6675k::read_max6675k()
{

}



int read_max6675k::init_sensor()
{

    if (wiringPiSetup () == -1)
        return 1;

    pinMode(CLK, OUTPUT);
    pinMode(DBIT, INPUT);
    pinMode(CS, OUTPUT);

    digitalWrite(CS, HIGH);
    digitalWrite(CLK, LOW);

}

double read_max6675k::update_val()
{

    SENSOR_VALUE = Thermal_Couple_Read();
    Ctemp = SENSOR_VALUE * 0.25;
    Ftemp = (Ctemp * 9 / 5) + 32;

    return Ftemp;

}


int Thermal_Couple_Read()
{

    int value = 0;
    // init sensor
    digitalWrite(CS, LOW);
    delay(2);
    digitalWrite(CS, HIGH);
    delay(200);

    // Read the chip and return the raw temperature value
    //Bring CS pin low to allow us to read the data from
    //the conversion process

    digitalWrite(CS, LOW);
    // Cycle the clock for dummy bit 15
    digitalWrite(CLK, HIGH);
    // delay(1);
    digitalWrite(CLK, LOW);


    //Read bits 14-3 from MAX6675 for the Temp.
    //Loop for each bit reading
    //the value and storing the final value in 'temp'

    int i;
    for (i = 14; i >= 0; i--)
    {
        digitalWrite(CLK, HIGH);
        //delay(1);
        value += digitalRead(DBIT) << i;
        digitalWrite(CLK, LOW);
    }

    // check bit D2 if HIGH no sensor
    if ((value & 0x04) == 0x04) return -1;
    // shift right three places
        return value >> 3;

}
