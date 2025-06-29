#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Mfill.h"
#include "Vfill.h"
#include "Vsort.h"
#include "Msort.h"
#include "Measurement.h"

clock_t Res[measurements_number];

float MeasurementProcessing()
{
    long int Sum;
    float AverageValue;
    clock_t buf;
    int L = rejected_number, R = measurements_number - 1, k = rejected_number;

    for (int j = 0; j < min_max_number; j++)
    {
        for (int i = L; i < R; i++)
        {
            if (Res[i] > Res[i + 1])
            {
                buf = Res[i];
                Res[i] = Res[i + 1];
                Res[i + 1] = buf;
                k = i;
            }
        }
        R = k;
        for (int i = R - 1; i >= L; i--)
        {
            if (Res[i] > Res[i + 1])
            {
                buf = Res[i];
                Res[i] = Res[i + 1];
                Res[i + 1] = buf;
                k = i;
            }
        }
        L = k + 1;
    }

    Sum = 0;
    for (int i = rejected_number + min_max_number; i < measurements_number - min_max_number; i++)
        Sum = Sum + Res[i];
    AverageValue = (float)Sum / (float)(measurements_number - 2 * min_max_number - rejected_number);
    return AverageValue;
}
void selection_measurement3Mt(int x)
{
    for (int i = 0; i < measurements_number; i++)
    {
        if (x == 1) // ordered array
        {
            OrderedMtfill();
            Res[i] = selection3Mt();
        }
        else if (x == 2) // backordered array
        {
            Back_orderedMtfill();
            Res[i] = selection3Mt();
        }
        else if (x == 3) // random array
        {
            RandomMtfill();
            Res[i] = selection3Mt();
        }
    }
}
void selection_measurement3Vt(int x)
{
    for (int i = 0; i < measurements_number; i++)
    {
        if (x == 1) // ordered array
        {
            OrderedVtfill();
            Res[i] = selection3Vt();
        }
        else if (x == 2) // back-ordered array
        {
            Back_orderedVtfill();
            Res[i] = selection3Vt();
        }
        else if (x == 3) // random array
        {
            RandomVtfill();
            Res[i] = selection3Vt();
        }
    }
}
void selection_measurement5Mt(int x)
{
    for (int i = 0; i < measurements_number; i++)
    {
        if (x == 1) // ordered array
        {
            OrderedMtfill();
            Res[i] = selection5Mt();
        }
        else if (x == 2) // backordered array
        {
            Back_orderedMtfill();
            Res[i] = selection5Mt();
        }
        else if (x == 3) // random array
        {
            RandomMtfill();
            Res[i] = selection5Mt();
        }
    }
}
void selection_measurement5Vt(int x)
{
    for (int i = 0; i < measurements_number; i++)
    {
        if (x == 1) // ordered array
        {
            OrderedVtfill();
            Res[i] = selection5Vt();
        }
        else if (x == 2) // back-ordered array
        {
            Back_orderedVtfill();
            Res[i] = selection5Vt();
        }
        else if (x == 3) // random array
        {
            RandomVtfill();
            Res[i] = selection5Vt();
        }
    }
}
void exchange_measurement1Mt(int x)
{
    for (int i = 0; i < measurements_number; i++)
    {
        if (x == 1) // ordered array
        {
            OrderedMtfill();
            Res[i] = exchange1Mt();
        }
        else if (x == 2) // backordered array
        {
            Back_orderedMtfill();
            Res[i] = exchange1Mt();
        }
        else if (x == 3) // random array
        {
            RandomMtfill();
            Res[i] = exchange1Mt();
        }
    }
}
void exchange_measurement1Vt(int x)
{
    for (int i = 0; i < measurements_number; i++)
    {
        if (x == 1) // ordered array
        {
            OrderedVtfill();
            Res[i] = exchange1Vt();
        }
        else if (x == 2) // back-ordered array
        {
            Back_orderedVtfill();
            Res[i] = exchange1Vt();
        }
        else if (x == 3) // random array
        {
            RandomVtfill();
            Res[i] = exchange1Vt();
        }
    }
}
