#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Vsort.h"
#include <time.h>
clock_t selection3Vt ()
{
    long int Min, Max, L, R, imin, imax;
    clock_t time_start, time_stop;
    time_start = clock();
    L=0;
    R=V-1;
    while (L<R)
    {
        Min=Vt[L];
        imin=L;
        Max=Vt[L];
        imax=L;
        for(long int i=L+1; i<R+1; i++)
        {
            if (Vt[i] < Min)
            {
                Min=Vt[i];
                imin=i;
            }
            else if (Vt[i] > Max)
            {
                Max=Vt[i];
                imax=i;
            }
        }
        Vt[imin]=Vt[L];
        Vt[L]=Min;
        if (imax==L) Vt[imin]=Vt[R];
        else Vt[imax]=Vt[R];
        Vt[R]=Max;
        L=L+1;
        R=R-1;
    }
    time_stop = clock();
    return time_stop - time_start;
}
clock_t selection5Vt ()
{
    long int Min, imin;
    clock_t time_start, time_stop;
    time_start = clock();
    for(long int s=0; s<V-1; s++)
    {
        Min=Vt[s];
        imin=s;
        for(long int i=s+1; i<V; i++)
            if (Vt[i]<Min)
            {
                Min=Vt[i];

                imin=i;
            }
        if (imin!=s)
        {
            Vt[imin]=Vt[s];
            Vt[s]=Min;
        }
    }
    time_stop = clock();
    return time_stop - time_start;
}

clock_t exchange1Vt ()
{
    long int tmp;
    clock_t time_start, time_stop;
    time_start = clock();
    for(long int R=V-1; R>0; R--)
    {
        for(long int i=0; i<R; i++)
            if (Vt[i]>Vt[i+1])
            {
                tmp=Vt[i];
                Vt[i]=Vt[i+1];
                Vt[i+1]=tmp;
            }
    }
    time_stop = clock();
    return time_stop - time_start;
}
