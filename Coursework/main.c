#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "common.h"
#include "Mfill.h"
#include "Vfill.h"
#include "Vsort.h"
#include "Msort.h"
#include "Measurement.h"
void GotoXY(int X, int Y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}
void colour(int i)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut,i);
}
void ConsoleCursorVisible(int show, short size)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show;
    structCursorInfo.dwSize = size;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void submenu( int q)
{
    system("cls");
    ConsoleCursorVisible(0, 100);
    const char* submenuOptions[] = {"Ordered", "Back-ordered", "Random", "Back to main menu"};
    int numSubOptions = sizeof(submenuOptions) / sizeof(submenuOptions[0]);
    int active_submenu = 0;
    char key;
    float time;
    while (1)
    {
        colour(10);
        GotoXY(33, 12);
        printf("Select the next option from this list:\n");
        GotoXY(35, 13);
        printf("Then press enter on the keyboard.\n");
        colour(9);
        int x = 45, y = 17;
        GotoXY(x, y);

        for (int i = 0; i < numSubOptions; i++)
        {
            GotoXY(x, y++);
            if (i == active_submenu)
            {
                colour(11);
                printf("* %s * ", submenuOptions[i]);
            }
            else
                printf("  %s   ", submenuOptions[i]);
            colour(9);
        }

        key = _getch();
        if (key == -32) key = _getch();
        switch (key)
        {
        case 27:
            exit(0);
        case 72:
            if (active_submenu > 0)
                active_submenu--;
            break;
        case 80:
            if (active_submenu < numSubOptions - 1)
                active_submenu++;
            break;
        case 13:
            switch (active_submenu)
            {
            case 0:
                system("CLS");
                if(q==1)
                {
                    colour(10);
                    printf("You chosed ordered array and selection3 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    OrderedMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection3Mt ();
                    OutputMt();
                    colour(10);
                    selection_measurement3Mt(1);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    OrderedVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection3Vt ();
                    OutputVt();
                    colour(10);
                    selection_measurement3Vt(1);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                else if(q==2)
                {
                    colour(10);
                    printf("You chosed ordered array and selection5 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    OrderedMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection5Mt ();
                    OutputMt();
                    colour(10);
                    selection_measurement5Mt(1);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    OrderedVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection5Vt ();
                    OutputVt();
                    colour(10);
                    selection_measurement5Vt(1);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                else if(q==3)
                {
                    colour(10);
                    printf("You chosed ordered array and exchange1 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    OrderedMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    exchange1Mt ();
                    OutputMt();
                    colour(10);
                    exchange_measurement1Mt(1);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    OrderedVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    exchange1Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    exchange_measurement1Vt(1);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                getch();
                system("CLS");
                break;
            case 1:
                colour(11);
                system("CLS");
                if(q==1)
                {
                    colour(10);
                    printf("You chosed back-ordered array and selection3 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    Back_orderedMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection3Mt ();
                    OutputMt();
                    colour(10);
                    selection_measurement3Mt(2);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    Back_orderedVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    selection3Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    selection_measurement3Vt(2);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                else if(q==2)
                {
                    colour(10);
                    printf("You chosed back-ordered array and selection5 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    Back_orderedMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection5Mt ();
                    OutputMt();
                    colour(10);
                    selection_measurement5Mt(2);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    Back_orderedVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    selection5Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    selection_measurement5Vt(2);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                else if(q==3)
                {
                    colour(10);
                    printf("You chosed back-ordered array and exchange1 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    Back_orderedMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    exchange1Mt ();
                    OutputMt();
                    colour(10);
                    exchange_measurement1Mt(2);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    Back_orderedVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    exchange1Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    exchange_measurement1Vt(2);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                getch();
                system("CLS");
                break;
            case 2:
                colour(11);
                system("CLS");
                if(q==1)
                {
                    colour(10);
                    printf("You chosed random array and selection3 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    RandomMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection3Mt ();
                    OutputMt();
                    colour(10);
                    selection_measurement3Mt(3);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    RandomVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    selection3Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    selection_measurement3Vt(3);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                else if(q==2)
                {
                    colour(10);
                    printf("You chosed random array and selection5 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    RandomMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    selection5Mt ();
                    OutputMt();
                    colour(10);
                    selection_measurement5Mt(3);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    RandomVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    selection5Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    selection_measurement5Vt(3);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                else if(q==3)
                {
                    colour(10);
                    printf("You chosed random array and exchange1 sorting\n");
                    printf("3D array before:\n");
                    colour(7);
                    RandomMtfill();
                    OutputMt();
                    colour(10);
                    printf("After sorting:\n");
                    colour(7);
                    exchange1Mt ();
                    OutputMt();
                    colour(10);
                    exchange_measurement1Mt(3);
                    time=MeasurementProcessing();
                    printf("  Array[%d][%d][%d], Time= %f\n\n",P,M,N,time);
                    printf("Vector array before:\n");
                    colour(7);
                    RandomVtfill();
                    OutputVt();
                    colour(10);
                    printf("After sorting:\n");
                    exchange1Vt ();
                    colour(7);
                    OutputVt();
                    colour(10);
                    exchange_measurement1Vt(3);
                    time=MeasurementProcessing();
                    printf("Vector`s size= %d: Time= %f\n",V,time);
                    colour(7);
                }
                getch();
                system("CLS");
                break;
            case 3:
                return;
            }
            break;
        }
    }
}
void menu()
{
    system("cls");
    ConsoleCursorVisible(0, 100);
    const char* menuOptions[] = {"selection3","selection5 ","exchange1","Table&Exit"};
    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int active_menu = 0;
    char key;
    while (1)
    {
        colour(10);
        GotoXY(31, 12);
        printf("To select any option, use two battons:\n");
        GotoXY(39, 13);
        printf("the up and down arrows.\n");
        GotoXY(35, 14);
        printf("Then press enter on the keyboard.\n");

        colour(9);
        int x = 45, y = 17;
        GotoXY(x, y);

        for (int i = 0; i < numOptions; i++)
        {
            GotoXY(x, y++);
            if (i == active_menu)
            {
                colour(11);
                printf("* %s * ",  menuOptions[i]);
            }
            else
                printf("  %s   ", menuOptions[i]);
            colour(9);
        }
        key = _getch();
        if (key == -32) key = _getch();
        switch (key)
        {
        case 27:
            exit(0);
        case 72:
            if (active_menu > 0)
                active_menu--;
            break;
        case 80:
            if (active_menu < numOptions - 1)
                active_menu++;
            break;
        case 13:
            switch (active_menu)
            {
            case 0:
                system("CLS");
                submenu(1);
                getch();
                system("CLS");
                break;
            case 1:
                system("CLS");
                submenu(2);
                getch();
                system("CLS");
                break;
            case 2:
                system("CLS");
                submenu(3);
                getch();
                system("CLS");
                break;
            case 3:
                colour(11);
                GotoXY(45, 24);
                system("CLS");
                Table ();
                exit(0);
                break;
            }
            break;
        }
    }
}
int main()
{
    Mt = (long int***) malloc(P * sizeof(long int**));
    for (long int k = 0; k < P; k++)
    {
        Mt[k] = (long int**) malloc(M * sizeof(long int*));
        for (long int i = 0; i < M; i++)
            Mt[k][i] = (int*) malloc(N * sizeof(long int));
    }
    menu();
    for (long int k = 0; k < P; k++)
    {
        for (long int i = 0; i < M; i++)
            free(Mt[k][i]);
        free(Mt[k]);
    }
    free(Mt);
    return 0;
}
