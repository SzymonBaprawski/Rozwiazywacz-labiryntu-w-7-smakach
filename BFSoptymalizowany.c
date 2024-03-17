#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie_z_pliku.h"
#include <time.h>

void usuwanie_zbednych_punktow(int **kolejka, int *koniec, int start_x, int start_y, int koniec_x, int koniec_y){
    int liczba_zmian = 1;
    int liczba_sasiadow = 0;

    while (liczba_zmian != 0){
        liczba_zmian = 0;
        for (int i = 0; i < *koniec; i++){
            liczba_sasiadow = 0;
            for (int j = 0; j < *koniec; j++){
                if (j != i){
                    if (kolejka[i][0] - 1 == kolejka[j][0] && kolejka[i][1] == kolejka[j][1]){
                        liczba_sasiadow++;
                    }
                    if (kolejka[i][0] + 1 == kolejka[j][0] && kolejka[i][1] == kolejka[j][1]){
                        liczba_sasiadow++;
                    }
                    if (kolejka[i][0] == kolejka[j][0] && kolejka[i][1] - 1 == kolejka[j][1]){
                        liczba_sasiadow++;
                    }
                    if (kolejka[i][0] == kolejka[j][0] && kolejka[i][1] + 1 == kolejka[j][1]){
                        liczba_sasiadow++;
                    }
                }
            }
            if (liczba_sasiadow == 1){
                if (kolejka[i][0] != start_x || kolejka[i][1] != start_y){
                    if (kolejka[i][0] != koniec_x || kolejka[i][1] != koniec_y){
                        for (int j = i; j < *koniec-1; j++){
                            kolejka[j][0] = kolejka[j+1][0];
                            kolejka[j][1] = kolejka[j+1][1];
                        }
                        *koniec = *koniec - 1;
                        liczba_zmian++;     
                    }
                }
            }
        }
    }
}  


void wytycz_sciezke (int **kolejka, int koniec){
    char kierunek = ' '; //N - north, S - south, W - west, E - east
    int kroki = 0;
    
    //kierunek początkowy
    if (kolejka[0][0] < kolejka[1][0]){
        printf("kierunek początkowy: E\n");
        kierunek = 'E';
    } else if (kolejka[0][0] > kolejka[1][0]){
        printf("kierunek początkowy: W\n");
        kierunek = 'W';
    } else if (kolejka[0][1] < kolejka[1][1]){
        printf("kierunek początkowy: S\n");
        kierunek = 'S';
    } else if (kolejka[0][1] > kolejka[1][1]){
        printf("kierunek początkowy: N\n");
        kierunek = 'N';
    }

    for (int i = 1; i < koniec; i++){
        if (kierunek == 'E'){
            if (kolejka[i][0] > kolejka[i-1][0]){
                kroki++;
            } else {
                printf("Forward %d\n", kroki);
                kroki = 1;
                if (kolejka[i][1] > kolejka[i-1][1]){
                    printf("Turn right\n");
                    kierunek = 'S';
                } else {
                    printf("Turn left\n");
                    kierunek = 'N';
                }
         }
        } else if (kierunek == 'W'){
            if (kolejka[i][0] < kolejka[i-1][0]){
                kroki++;
            } else {
                printf("Forward %d\n", kroki);
                kroki = 1;
                if (kolejka[i][1] > kolejka[i-1][1]){
                    printf("Turn left\n");
                    kierunek = 'S';
                } else {
                    printf("Turn right\n");
                    kierunek = 'N';
                }
            }
        } else if (kierunek == 'S'){
            if (kolejka[i][1] > kolejka[i-1][1]){
                kroki++;
            } else {
                printf("Forward %d\n", kroki);
                kroki = 1;
                if (kolejka[i][0] > kolejka[i-1][0]){
                    printf("Turn left\n");
                    kierunek = 'E';
                } else {
                    printf("Turn right\n");
                    kierunek = 'W';
                }
            }
        } else if (kierunek == 'N'){
            if (kolejka[i][1] < kolejka[i-1][1]){
                kroki++;
            } else {
                printf("Forward %d\n", kroki);
                kroki = 1;
                if (kolejka[i][0] > kolejka[i-1][0]){
                    printf("Turn right\n");
                    kierunek = 'E';
                } else {
                    printf("Turn left\n");
                    kierunek = 'W';
                }
            }
        }
    }
    printf("Forward %d\n", kroki);
    printf("Koniec\n");
}



void bfs( int **tablica, int szerokosc, int wysokosc, int x, int y, int x_koniec, int y_koniec){
    int **odwiedzone;
    alokuj_pamiec(szerokosc, wysokosc, &odwiedzone);

    for (int i = 0; i < szerokosc; i++){
        for (int j = 0; j < wysokosc; j++){
            odwiedzone[i][j] = 0;
        }
    }

    int **kolejka;
    alokuj_pamiec(1, 2, &kolejka);

    int poczatek = 0;
    int koniec = 1;

    kolejka[0][0] = x;
    kolejka[0][1] = y;

    while (poczatek != koniec){
        int x = kolejka[poczatek][0];
        int y = kolejka[poczatek][1];
        odwiedzone[x][y] = 1;
        poczatek++;

        if (x == x_koniec && y == y_koniec){
            break;
        }

        if (x > 0 && tablica[x-1][y] != 1 && odwiedzone[x-1][y] == 0){
            rozszerz_pamiec(koniec + 1, 2, &kolejka);
            kolejka[koniec][0] = x-1;
            kolejka[koniec][1] = y;
            koniec++;
            odwiedzone[x-1][y] = 1;
        }
        if (x < szerokosc-1 && tablica[x+1][y] != 1 && odwiedzone[x+1][y] == 0){
            rozszerz_pamiec(koniec + 1, 2, &kolejka);
            kolejka[koniec][0] = x+1;
            kolejka[koniec][1] = y;
            koniec++;
            odwiedzone[x+1][y] = 1;
        }
        if (y > 0 && tablica[x][y-1] != 1 && odwiedzone[x][y-1] == 0){
            rozszerz_pamiec(koniec + 1, 2, &kolejka);
            kolejka[koniec][0] = x;
            kolejka[koniec][1] = y-1;
            koniec++;
             
            odwiedzone[x][y-1] = 1;

        }
        if (y < wysokosc-1 && tablica[x][y+1] != 1 && odwiedzone[x][y+1] == 0){
             rozszerz_pamiec(koniec + 1, 2, &kolejka);
            kolejka[koniec][0] = x;
            kolejka[koniec][1] = y+1;
            koniec++;
             
            odwiedzone[x][y+1] = 1;
        }
    }

    usuwanie_zbednych_punktow(kolejka, &koniec, x, y, x_koniec, y_koniec);

    wytycz_sciezke(kolejka, koniec);
}

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

    printf("Start: %d %d\nKoniec: %d %d\n", x, y, x_koniec, y_koniec);

    //wypisz_tablice(szerokosc, wysokosc, tablica);

    bfs(tablica, szerokosc, wysokosc, x, y, x_koniec, y_koniec);
    
    clock_t koniec = clock();
    double czas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Czas wykonywania: %f\n", czas);


    return 0;
}