#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Msort.h"
#include <time.h>
clock_t selection3Mt ()
{
    clock_t time_start, time_stop;
    time_start = clock();
    long int L, A, R, B, imin, jmin, imax, jmax, Min, Max;

    for (long int k = 0; k < P; k++)
    {
        L = 0;
        A = 0;
        R = N - 1;
        B = M - 1;
        while (L <= R)
        {
            imin = A;
            jmin = L;
            imax = A;
            jmax = L;
            Min = Mt[k][A][L];
            Max = Mt[k][A][L];
            for (long int i = A; i < M; i++)
            {
                if (Mt[k][i][L] < Min)
                {
                    imin = i;
                    jmin = L;
                    Min = Mt[k][i][L];
                }
                else if (Mt[k][i][L] > Max)
                {
                    imax = i;
                    jmax = L;
                    Max = Mt[k][i][L];
                }
            }
            for (long int j = L + 1; j < R; j++)
            {
                for (long int i = 0; i < M; i++)
                {
                    if (Mt[k][i][j] < Min)
                    {
                        imin = i;
                        jmin = j;
                        Min = Mt[k][i][j];
                    }
                    else if (Mt[k][i][j] > Max)
                    {
                        imax = i;
                        jmax = j;
                        Max = Mt[k][i][j];
                    }
                }
            }
            for (long int i = 0; i < B + 1; i++)
            {
                if (Mt[k][i][R] < Min)
                {
                    imin = i;
                    jmin = R;
                    Min = Mt[k][i][R];
                }
                else if (Mt[k][i][R] > Max)
                {
                    imax = i;
                    jmax = R;
                    Max = Mt[k][i][R];
                }
            }
            Mt[k][imin][jmin] = Mt[k][A][L];
            Mt[k][A][L] = Min;
            if (jmax == L && imax == A)
                Mt[k][imin][jmin] = Mt[k][B][R];
            else
                Mt[k][imax][jmax] = Mt[k][B][R];
            Mt[k][B][R] = Max;
            A++;
            B--;
            if (A == M)
            {
                L++;
                R--;
                A = 0;
                B = M - 1;
            }
        }
        if ((L - R) == 2)
        {
            L -= 1;
            A = 0;
            B = M - 1;
            while (A < B)
            {
                imin = A;
                imax = A;
                Min=Mt[k][A][L];
                Max=Mt[k][A][L];
                for (long int i = A + 1; i < B + 1; i++)
                {
                    if (Mt[k][i][L] < Min)
                    {
                        imin = i;
                        Min=Mt[k][i][L];
                    }
                    else if (Mt[k][i][L] > Max)
                    {
                        imax = i;
                        Max=Mt[k][i][L];
                    }
                }
                Mt[k][imin][L] = Mt[k][A][L];
                Mt[k][A][L] = Min;
                if (imax == A)
                    Mt[k][imin][L] = Mt[k][B][L];
                else
                    Mt[k][imax][L] = Mt[k][B][L];
                A++;
                B--;
            }
        }
    }
    time_stop = clock();
    return time_stop - time_start;
}
clock_t selection5Mt ()
{
    long int Min, imin, jmin, o;
    clock_t time_start, time_stop;
    time_start = clock();
    for(long int k = 0; k < P; k++)
    {
        for(long int j = 0; j < N; j++)
        {
            for(long int i = 0; i < M; i++)
            {
                jmin = j;
                imin = i;
                Min = Mt[k][imin][jmin];
                for (long int q = j; q < N; q++)
                {
                    o = (q == j) ? (i + 1) : 0;
                    for(long int b = o ; b < M; b++)
                    {
                        if (Mt[k][b][q] < Min)
                        {
                            imin = b;
                            jmin = q;
                            Min = Mt[k][imin][jmin];
                        }
                    }
                }
                if (jmin != j || imin != i)
                {
                    Mt[k][imin][jmin] = Mt[k][i][j];
                    Mt[k][i][j] = Min;
                }
            }
        }
    }
    time_stop = clock();
    return time_stop - time_start;
}
clock_t exchange1Mt ()
{
    long int q, b, tmp;
    clock_t time_start, time_stop;
    time_start = clock();
    for(long int k = 0; k < P; k++)
    {
        for(long int j = N - 1; j >= 0; j--)
        {
            for(long int i = M - 1; i >= 0; i--)
            {
                for(q = 0; q < j; q++)
                {
                    for(b = 0; b < M - 1; b++)
                    {
                        if(Mt[k][b][q] > Mt[k][b+1][q])
                        {
                            tmp = Mt[k][b][q];
                            Mt[k][b][q] = Mt[k][b+1][q];
                            Mt[k][b+1][q] = tmp;
                        }
                    }
                    if(Mt[k][M-1][q] > Mt[k][0][q+1])
                    {
                        tmp = Mt[k][M-1][q];
                        Mt[k][M-1][q] = Mt[k][0][q+1];
                        Mt[k][0][q+1] = tmp;
                    }
                }
                for(b = 0; b < i; b++)
                {
                    if(Mt[k][b][j] > Mt[k][b+1][j])
                    {
                        tmp = Mt[k][b][j];
                        Mt[k][b][j] = Mt[k][b+1][j];
                        Mt[k][b+1][j] = tmp;
                    }
                }
            }
        }
    }
    time_stop = clock();
    return time_stop - time_start;
}
