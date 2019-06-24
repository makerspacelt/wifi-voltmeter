#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include <SPI.h>
#include "global.h"


void initDisplay();
void screenRepaint();
void showBar( bool = true );
void showWifi( bool = true );
void showScale( bool = true );
void showVoltage( bool = true );

#endif // DISPLAY_H