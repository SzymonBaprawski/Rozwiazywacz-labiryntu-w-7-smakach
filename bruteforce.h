#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "czytanie_z_pliku.h"
#include<time.h>

struct p{
    int w;
    int k;
    int kierunek; // "G"->0, "P"-> 1, "D"->2, "L"-> 3
    int f;
}p;


void forward(int kierunek);

int sum(int a, int b, int c, int d);

void turnR();

void turnL();

#endif