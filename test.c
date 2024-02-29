#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie_z_pliku.h"

int main (int argc, char *argv[]){

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

    printf("Szerokość: %d\nWysokość: %d\n", szerokosc, wysokosc);

    //deklaracja tablicy
    int **tablica;
    alokuj_pamiec(szerokosc, wysokosc, &tablica);

    wczytaj_z_pliku(argv[1], szerokosc, wysokosc, tablica);

    //wypisz 
    wypisz_tablice(szerokosc, wysokosc, tablica);

    return 0;
}