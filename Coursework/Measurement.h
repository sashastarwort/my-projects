#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <time.h>

#define measurements_number 28
#define rejected_number 2
#define min_max_number 3
extern clock_t Res[measurements_number];
float MeasurementProcessing();
void selection_measurement3Mt (int x);
void selection_measurement5Mt (int x);
void exchange_measurement1Mt (int x);
void selection_measurement3Vt (int x);
void selection_measurement5Vt (int x);
void exchange_measurement1Vt (int x);

#endif MEASUREMENT_H
