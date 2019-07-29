#ifndef GLOBAL_H
#define GLOBAL_H

#define SCALE_RAW 1
#define SCALE_FET 2


// struct globalState {
//     int min_range = 0;
//     int max_range = 3;
//     float adc_ratio[4] = {1.100, 1.100, 1.100, 1.100};
//     int adc_min = 95;
//     int adc_max = 995;
//     int adc_now = 0;
//     int adc_avg = 0;
//     int avg_samples = 20;
//     int voltage = 0;
//     int scale_type = SCALE_FET;
//     int scale = 1;
//     int wifi = 0;
// };

struct globalState {
    int min_range = 0;
    int max_range = 2;
    float adc_ratio[4] = {0.205, 0.325, 0.358, 1};
    int adc_min = 60;
    int adc_max = 665;
    int adc_now = 0;
    int adc_avg = 0;
    int avg_samples = 20;
    int voltage = 0;
    int scale_type = SCALE_RAW;
    int scale = 1;
    int wifi = 0;
};

extern globalState state;


#endif // GLOBAL_H