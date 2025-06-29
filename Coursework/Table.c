#include <stdlib.h>
#include <stdio.h>

#include "table.h"
#include "common.h"
#include "Measurement.h"

void Table ()
{
    float o, b, r;
    printf("\t\t\t\t  Table for the array: P = %d, M = %d, N = %d\n\n", P, M, N);
    printf("\t\t\tOrdered\t\t\tRandom\t\t\tBack-ordered\n\n");

    selection_measurement3Mt(1);
    o = MeasurementProcessing();
    selection_measurement3Mt(3);
    r = MeasurementProcessing();
    selection_measurement3Mt(2);
    b = MeasurementProcessing();
    printf("Selection3\t\t%f\t\t%f\t\t%f\n\n", o, r, b);

    selection_measurement5Mt(1);
    o = MeasurementProcessing();
    selection_measurement5Mt(3);
    r = MeasurementProcessing();
    selection_measurement5Mt(2);
    b = MeasurementProcessing();
    printf("Selection5\t\t%f\t\t%f\t\t%f\n\n", o, r, b);

    exchange_measurement1Mt(1);
    o = MeasurementProcessing();
    exchange_measurement1Mt(3);
    r = MeasurementProcessing();
    exchange_measurement1Mt(2);
    b = MeasurementProcessing();
    printf("Exchange1\t\t%f\t\t%f\t\t%f\n\n", o, r, b);

    printf("\t\t\t\t  Table for the vector: V = %d\n\n", V);
    printf("\t\t\tOrdered\t\t\tRandom\t\t\tBack-ordered\n\n");

    selection_measurement3Vt(1);
    o = MeasurementProcessing();
    selection_measurement3Vt(3);
    r = MeasurementProcessing();
    selection_measurement3Vt(2);
    b = MeasurementProcessing();
    printf("Selection3\t\t%f\t\t%f\t\t%f\n\n", o, r, b);

    selection_measurement5Vt(1);
    o = MeasurementProcessing();
    selection_measurement5Vt(3);
    r = MeasurementProcessing();
    selection_measurement5Vt(2);
    b = MeasurementProcessing();
    printf("Selection5\t\t%f\t\t%f\t\t%f\n\n", o, r, b);

    exchange_measurement1Vt(1);
    o = MeasurementProcessing();
    exchange_measurement1Vt(3);
    r = MeasurementProcessing();
    exchange_measurement1Vt(2);
    b = MeasurementProcessing();
    printf("Exchange1\t\t%f\t\t%f\t\t%f\n\n", o, r, b);
}
