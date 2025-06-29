#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Mfill.h"

void OrderedMtfill()
{
    int num=1;
    for (long int k=0; k<P; k++)
    {
        for (long int j=0; j<N; j++)
        {
            for (long int i=0; i<M; i++)
            {
                Mt[k][i][j] = num++;
            }
        }
    }
}

void Back_orderedMtfill()
{
    long int num = P * M * N;
    for (long int k = 0; k < P; k++)
    {
        for (long int j = 0; j < N; j++)
        {
            for (long int i = 0; i < M; i++)
            {
                Mt[k][i][j] = num--;
            }
        }
    }
}

void RandomMtfill()
{
    for (long int k = 0; k < P; k++)
        for (long int j = 0; j < N; j++)
            for (long int i = 0; i < M; i++)
                Mt[k][i][j] = rand() % (P * M * N);
}

void OutputMt()
{
    for (long int k = 0; k < P; k++)
    {
        printf("\nP = %d\n", k);
        for (long int i = 0; i < M; i++)
        {
            for (long int j = 0; j < N; j++)
            {
                printf("%d ", Mt[k][i][j]);
            }
            printf("\n");
        }
    }
}
