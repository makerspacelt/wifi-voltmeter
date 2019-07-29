#ifndef MEASURE_H
#define MEASURE_H

#include <Arduino.h>
#include "global.h"


#define MEASURE_PIN A0
#define SCALE_10_PIN D5
#define SCALE_100_PIN D6
#define SCALE_1000_PIN D7


void readVoltage();
void setScale( int );
void setScaleRaw( int );
void setScaleFet( int );

#endif // MEASURE_H