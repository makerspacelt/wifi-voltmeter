#ifndef GLOBAL_H
#define GLOBAL_H


struct globalState {
    float adc_ratio = 1.000;
    int adc_now = 0;
    int adc_avg = 0;
    int avg_samples = 30;
    int voltage = 0;
    int scale = 1;
    bool wifi = 0;
};

extern globalState state;


#endif // GLOBAL_H