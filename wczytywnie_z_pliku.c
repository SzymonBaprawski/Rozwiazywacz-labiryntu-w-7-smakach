#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie_z_pliku.h"

int sprawdz_szerokosc(char *nazwa_pliku){
    FILE *plik = fopen(nazwa_pliku, "r");
    if (plik == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }
    int szerokosc = 0;
    char znak;
    while (fscanf(plik, "%c", &znak) != EOF){
        if (znak == '\n'){
            break;
        }
        szerokosc++;
    }
    fclose(plik);
    return szerokosc;
}

int sprawdz_wysokosc(char *nazwa_pliku){
    FILE *plik = fopen(nazwa_pliku, "r");
    if (plik == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return 1;
    }
    int wysokosc = 0;
    char znak;
    while (fscanf(plik, "%c", &znak) != EOF){
        if (znak == '\n'){
            wysokosc++;
        }
    }
    fclose(plik);
    return wysokosc;
}

void alokuj_pamiec(int szerokosc, int wysokosc, int ***tablica){
    *tablica = (int**)malloc(wysokosc * sizeof(int*));
    for (int i = 0; i < wysokosc; i++){
        (*tablica)[i] = (int*)malloc(szerokosc * sizeof(int));
    }
}

void wczytaj_z_pliku(char *nazwa_pliku, int szerokosc, int wysokosc, int **tablica){
    FILE *plik = fopen(nazwa_pliku, "r");
    if (plik == NULL){
        printf("Nie udało się otworzyć pliku\n");
        return;
    }
    for (int i = 0; i <= wysokosc; i++){
        for (int j = 0; j <= szerokosc; j++){
            //X = 1, ' ' = 0, P = 2, K = 3
            char znak;
            fscanf(plik, "%c", &znak);
            if (znak == 'X'){
                tablica[i][j] = 1;
            }
            else if (znak == ' '){
                tablica[i][j] = 0;
            }
            else if (znak == 'P'){
                tablica[i][j] = 2;
            }
            else if (znak == 'K'){
                tablica[i][j] = 3;
            }
        }
    }
    fclose(plik);
}

void wypisz_tablice(int szerokosc, int wysokosc, int **tablica){
    for (int i = 0; i < wysokosc; i++){
        for (int j = 0; j < szerokosc; j++){
            printf("%d", tablica[i][j]);
        }
        printf("\n");
    }
}
