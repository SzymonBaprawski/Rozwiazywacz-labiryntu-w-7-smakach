#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie_z_pliku.h"
#include <time.h>
#include <math.h>
#include <string.h>

double odleglosc_manhattan(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

double odleglosc_euklidesowa(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

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

int astar(int szerokosc, int wysokosc, int **tablica, int x, int y, int x_koniec, int y_koniec, int open_list[szerokosc * wysokosc][5], int *open_dlugosc, int closed_list[szerokosc * wysokosc][2], int *closed_dlugosc, char *heurestyka){
    int x_sasiad = 0;
    int y_sasiad = 0;
    int g = 0;
    int h = 0;
    int f = 0;
    int znaleziono = 0;
    int aktualny_f = 0;
    int aktualny_index = 0;

    //dodaj start do open_list
    open_list[*open_dlugosc][0] = x;
    open_list[*open_dlugosc][1] = y;
    open_list[*open_dlugosc][2] = 0; //f
    open_list[*open_dlugosc][3] = 0; //g
    open_list[*open_dlugosc][4] = 0; //h
    *open_dlugosc = *open_dlugosc + 1;

    while (*open_dlugosc > 0){
        //znajdź w open_list węzeł z najmniejszym f
        aktualny_f = open_list[0][2];
        aktualny_index = 0;
        for (int i = 0; i < *open_dlugosc; i++){
            if (open_list[i][2] < aktualny_f){
                aktualny_f = open_list[i][2];
                aktualny_index = i;
            }
        }

        //przenieś aktualny węzeł do closed_list
        closed_list[*closed_dlugosc][0] = open_list[aktualny_index][0];
        closed_list[*closed_dlugosc][1] = open_list[aktualny_index][1];
        *closed_dlugosc = *closed_dlugosc + 1;

        //usuń aktualny węzeł z open_list
        for (int i = aktualny_index; i < *open_dlugosc - 1; i++){
            open_list[i][0] = open_list[i + 1][0];
            open_list[i][1] = open_list[i + 1][1];
            open_list[i][2] = open_list[i + 1][2];
            open_list[i][3] = open_list[i + 1][3];
            open_list[i][4] = open_list[i + 1][4];
        }
        *open_dlugosc = *open_dlugosc - 1;

        //sprawdź czy aktualny węzeł to koniec
        if (closed_list[*closed_dlugosc - 1][0] == x_koniec && closed_list[*closed_dlugosc - 1][1] == y_koniec){
            znaleziono = 1;
            break;
        }

        //dodaj sąsiadów do open_list
        for (int i = 0; i < 4; i++){
            if (i == 0){
                x_sasiad = closed_list[*closed_dlugosc - 1][0] - 1;
                y_sasiad = closed_list[*closed_dlugosc - 1][1];
            } else if (i == 1){
                x_sasiad = closed_list[*closed_dlugosc - 1][0] + 1;
                y_sasiad = closed_list[*closed_dlugosc - 1][1];
            } else if (i == 2){
                x_sasiad = closed_list[*closed_dlugosc - 1][0];
                y_sasiad = closed_list[*closed_dlugosc - 1][1] - 1;
            } else if (i == 3){
                x_sasiad = closed_list[*closed_dlugosc - 1][0];
                y_sasiad = closed_list[*closed_dlugosc - 1][1] + 1;
            }

            //sprawdź czy sąsiad jest na planszy
            if (x_sasiad < 0 || x_sasiad >= szerokosc || y_sasiad < 0 || y_sasiad >= wysokosc){
                continue;
            }

            //sprawdź czy sąsiad jest ścianą
            if (tablica[x_sasiad][y_sasiad] == 1){
                continue;
            }

            //sprawdź czy sąsiad jest w closed_list
            int w_closed = 0;
            for (int j = 0; j < *closed_dlugosc; j++){
                if (closed_list[j][0] == x_sasiad && closed_list[j][1] == y_sasiad){
                    w_closed = 1;
                    break;
                }
            }
            if (w_closed == 1){
                continue;
            }

            //sprawdź czy sąsiad jest w open_list
            int w_open = 0;
            for (int j = 0; j < *open_dlugosc; j++){
                if (open_list[j][0] == x_sasiad && open_list[j][1] == y_sasiad){
                    w_open = 1;
                    break;
                }
            }
            if (w_open == 1){
                continue;
            }

            //oblicz g, h, f
            if (strcmp(heurestyka, "manhattan") == 0){
                g = closed_list[*closed_dlugosc - 1][3] + 1;
                h = odleglosc_manhattan(x_sasiad, y_sasiad, x_koniec, y_koniec);
            } else if (strcmp(heurestyka, "euklidesowa") == 0){
                g = closed_list[*closed_dlugosc - 1][3] + 1;
                h = odleglosc_euklidesowa(x_sasiad, y_sasiad, x_koniec, y_koniec);
            }
            f = g + h;

            //dodaj sąsiada do open_list
            open_list[*open_dlugosc][0] = x_sasiad;
            open_list[*open_dlugosc][1] = y_sasiad;
            open_list[*open_dlugosc][2] = f;
            open_list[*open_dlugosc][3] = g;
            open_list[*open_dlugosc][4] = h;
            *open_dlugosc = *open_dlugosc + 1;
        }
    }
    if (znaleziono == 1){
        return 1;
    } else {
        printf("Nie udało się znaleźć ścieżki\n");
        return 0;
    }
}

int main (int argc, char *argv[]){

    clock_t start = clock();

    char *heurestyka = "manhattan";

    if (argc < 2){
        printf("Za mało argumentów, brakuje pliku oraz heurestyki (manhattan/euklidesowa)\n");
        return 1;
    }else if (argc == 2){
        printf("Nie podano heurestyki, zostanie wykorzystana heurestyka manhattan (manhattan/euklidesowa)\n");
    } else if (argc == 3){
        if (strcmp(argv[2], "manhattan") != 0 && strcmp(argv[2], "euklidesowa") != 0){
            printf("Niepoprawna heurestyka, zostanie wykorzystana heurestyka manhattan (manhattan/euklidesowa)\n");
        } else {
            heurestyka = argv[2];
        }
    } else {
        printf("Za dużo argumentów, wymagana nazwa pliku z labiryntem i heurestyka (manhattan/euklidesowa)\n");
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

    int x = 0;
    int y = 0;
    int x_koniec = 0;
    int y_koniec = 0;

    int open_list[szerokosc * wysokosc][5]; // x y f g h
    int open_dlugosc = 0;
    int closed_list[szerokosc * wysokosc][2]; // x y
    int closed_dlugosc = 0;

    //znajdź start i koniec
    znajdz_start(szerokosc, wysokosc, tablica, &x, &y);
    znajdz_koniec(szerokosc, wysokosc, tablica, &x_koniec, &y_koniec);

    if (astar(szerokosc, wysokosc, tablica, x, y, x_koniec, y_koniec, open_list, &open_dlugosc, closed_list, &closed_dlugosc, heurestyka) == 1){
        //skopiowanie tablicy do plisty
        int **kolejka;
        alokuj_pamiec(szerokosc * wysokosc, 2, &kolejka);
        for (int i = 0; i < closed_dlugosc; i++){
            kolejka[i][0] = closed_list[i][0];
            kolejka[i][1] = closed_list[i][1];
        }

        usuwanie_zbednych_punktow(kolejka, &closed_dlugosc, x, y, x_koniec, y_koniec);

        /*printf("Scieżka:\n");
        for (int i = 0; i < closed_dlugosc; i++){
            printf("%d %d\n", kolejka[i][0], kolejka[i][1]);
        }*/

        wytycz_sciezke(kolejka, closed_dlugosc);

    }
    
    clock_t koniec = clock();
    double czas = (double)(koniec - start) / CLOCKS_PER_SEC;
    printf("Czas wykonywania: %f\n", czas);


    return 0;
}