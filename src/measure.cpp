#include "measure.h"


void readVoltage()
{
    state.adc_now = analogRead(A0);
//*
    if (state.adc_now > 995 && state.scale < 3) {
        setScale(state.scale+1);
        readVoltage();
    }
    if (state.adc_now < 95 && state.scale > 0) {
        setScale(state.scale-1);
        readVoltage();
    }
/* */
}


void setScale(int target_scale)
{
    digitalWrite(SCALE_10_PIN, LOW);
    digitalWrite(SCALE_100_PIN, LOW);
    digitalWrite(SCALE_1000_PIN, LOW);

    switch (target_scale) {
        case 0:
            pinMode(SCALE_10_PIN, INPUT);
            pinMode(SCALE_100_PIN, INPUT);
            pinMode(SCALE_1000_PIN, INPUT);
            break;
        case 1:
            pinMode(SCALE_10_PIN, OUTPUT);
            pinMode(SCALE_100_PIN, INPUT);
            pinMode(SCALE_1000_PIN, INPUT);
            break;
        case 2:
            pinMode(SCALE_10_PIN, INPUT);
            pinMode(SCALE_100_PIN, OUTPUT);
            pinMode(SCALE_1000_PIN, INPUT);
            break;
        case 3:
            pinMode(SCALE_10_PIN, INPUT);
            pinMode(SCALE_100_PIN, INPUT);
            pinMode(SCALE_1000_PIN,OUTPUT);
            break;
    }
    state.scale = target_scale;
    // give time for low pass filter on the input
    delay(3);
}
