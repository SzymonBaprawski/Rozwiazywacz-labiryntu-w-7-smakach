#ifndef CZYTANIE_Z_PLIKU_H
#define CZYTANIE_Z_PLIKU_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int m; //ilosc wierszy
    int n; //ilosc kolumn
    int maz[2049][2049]; //labirynt wypelniony "0"-> pusta kratka () ; "1"->sciana(X); "2"-> poczatek (P); "3"-> koniec (K)  
}maze;


#endif