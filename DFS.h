#ifndef DFS_H
#define DFS_H

#include <stdlib.h>
#include<stdio.h>


//jeden

typedef struct maze{
    int m; //ilosc wierszy
    int n; //ilosc kolumn
    int maz[2049][2049]; //labirynt wypelniony "0"-> pusta kratka () ; "1"->sciana(X); "2"-> poczatek (P); "3"-> koniec (K)  
}maze;

maze* returnmaze(FILE*plik);

// dwa

typedef struct stos {
    int kolumna;
    int wiersz;
    int kierunek;
    int *trasa;
    int ile; // nw czy jest set na zero xd
    struct stos * next;
} stos_type;

void pop(stos_type **top);

void push(stos_type **top, int k, int w, int kierunek, int* trasa);

void daj(stos_type *top);

//trzy

struct p{
    int w;
    int k;
    int kierunek; // "G"->0, "P"-> 1, "D"->2, "L"-> 3
}p;

//cztery

int sum(int a, int b, int c, int d);

void turnR();
void turnL();
void forward(int kierunek);

//void wypisz_wynik();



#endif