#include "measure.h"


void readVoltage()
{
    state.adc_now = analogRead(A0);
//*
    if (state.adc_now > state.adc_max && state.scale < state.max_range) {
        setScale(state.scale+1);
        readVoltage();
    }
    if (state.adc_now < state.adc_min && state.scale > state.min_range) {
        setScale(state.scale-1);
        readVoltage();
    }
/* */
}


void setScale(int target_scale)
{
    if (state.scale_type == SCALE_RAW) {
        return setScaleRaw(target_scale);
    }
    if (state.scale_type == SCALE_FET) {
        return setScaleFet(target_scale);
    }
}
void setScaleRaw(int target_scale)
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

void setScaleFet(int target_scale)
{
    pinMode(SCALE_10_PIN, OUTPUT);
    pinMode(SCALE_100_PIN, OUTPUT);
    pinMode(SCALE_1000_PIN, OUTPUT);

    switch (target_scale) {
        case 0:
            digitalWrite(SCALE_10_PIN, LOW);
            digitalWrite(SCALE_100_PIN, LOW);
            digitalWrite(SCALE_1000_PIN, LOW);
            break;
        case 1:
            digitalWrite(SCALE_10_PIN, HIGH);
            digitalWrite(SCALE_100_PIN, LOW);
            digitalWrite(SCALE_1000_PIN, LOW);
            break;
        case 2:
            digitalWrite(SCALE_10_PIN, LOW);
            digitalWrite(SCALE_100_PIN, HIGH);
            digitalWrite(SCALE_1000_PIN, LOW);
            break;
        case 3:
            digitalWrite(SCALE_10_PIN, LOW);
            digitalWrite(SCALE_100_PIN, LOW);
            digitalWrite(SCALE_1000_PIN, HIGH);
            break;
    }
    state.scale = target_scale;
    // give time for low pass filter on the input
    delay(3);
}
