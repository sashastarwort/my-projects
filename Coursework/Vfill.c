#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Vfill.h"

void OrderedVtfill()
{
    long int num = 0;
    for (long int i = 0; i < V; i++)
    {
        Vt[i] = num++;
    }
}

void Back_orderedVtfill()
{
    for (long int i = 0; i < V; i++)
    {
        Vt[i] = V - i;
    }
}

void RandomVtfill()
{
    srand(time(NULL));
    long int max =M*N*P, min = 0;
    for(long int j=0; j<V; j++)
    {
        Vt[j] = rand() % (P * M * N);
    }
}

void OutputVt()
{
    for (long int i = 0; i < V; i++)
    {
        printf("%d ", Vt[i]);
    }
    printf("\n\n");
}
