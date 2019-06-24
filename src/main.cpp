#include "main.h"

#include "display.h"
#include "measure.h"
#include "mqtt.h"



void setup()
{
    initDisplay();
    setScale(state.scale);
    screenRepaint();
    initMqtt();
}

void loop()
{
    updateWifiStatus();

    for (int v=0; v<state.avg_samples; v++) {
        int old_scale = state.scale;
        readVoltage();
        if (old_scale != state.scale) {
            v=0;
            state.adc_avg = state.adc_now;
            showScale();
        }
        state.adc_avg += state.adc_now;
        showBar();
    }
    state.adc_avg = state.adc_avg/state.avg_samples;
    // shows garbage near zero
    if (state.adc_avg < 10) {
        state.adc_avg = 0;
    }
    screenRepaint();
}

