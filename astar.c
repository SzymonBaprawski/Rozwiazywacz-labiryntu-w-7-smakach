#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie_z_pliku.h"
#include <time.h>
#include <math.h>





int main (int argc, char *argv[]){

    clock_t start = clock();


    if (argc != 2){
        printf("Niepoprawna liczba argumentów\n");
        return 1;
    }

    FILE *plik = fopen(argv[1], "r");
    if (plik == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }
    fclose(plik);

    //określenie szerokości i wysokości
    int szerokosc = sprawdz_szerokosc(argv[1]);
    int wysokosc = sprawdz_wysokosc(argv[1]);

    //printf("Szerokość: %d\nWysokość: %d\n", szerokosc, wysokosc);

    //deklaracja tablicy
    int **tablica;
    alokuj_pamiec(szerokosc, wysokosc, &tablica);

    wczytaj_z_pliku(argv[1], szerokosc, wysokosc, tablica);
    //wypisz_tablice(szerokosc, wysokosc, tablica);

    int x = 0;
    int y = 0;
    int x_koniec = 0;
    int y_koniec = 0;

    //znajdź start i koniec
    znajdz_start(szerokosc, wysokosc, tablica, &x, &y);
    znajdz_koniec(szerokosc, wysokosc, tablica, &x_koniec, &y_koniec);

    //printf("Start: %d %d\nKoniec: %d %d\n", x, y, x_koniec, y_koniec);

    wypisz_tablice(szerokosc, wysokosc, tablica);

    clock_t koniec = clock();
    double czas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Czas wykonywania: %f\n", czas);


    return 0;
}