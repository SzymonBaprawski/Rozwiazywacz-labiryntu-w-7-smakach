#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "wczytywanie_z_pliku.h"

void oznaczanie_pol (int **tablica, int szerokosc, int wysokosc, int x_koniec, int y_koniec, int x, int y){
    tablica[x][y] = 10;
    
    int liczba_zmian = 1;

    while(liczba_zmian>0){
        liczba_zmian = 0;
        for(int i = 0; i < szerokosc; i++){
            for(int j = 0; j < wysokosc; j++){
                if (tablica[i][j] >= 10){
                    if (i > 0){
                        if (tablica[i-1][j] == 0 || tablica[i-1][j] == 3){
                            tablica[i-1][j] = tablica[i][j] + 1;
                            liczba_zmian++;
                        }
                    }
                    if (i < szerokosc-1){
                        if (tablica[i+1][j] == 0 || tablica[i+1][j] == 3){
                            tablica[i+1][j] = tablica[i][j] + 1;
                            liczba_zmian++;
                        }
                    }
                    if (j > 0){
                        if (tablica[i][j-1] == 0 || tablica[i][j-1] == 3){
                            tablica[i][j-1] = tablica[i][j] + 1;
                            liczba_zmian++;
                        }
                    }
                    if (j < wysokosc-1){
                        if (tablica[i][j+1] == 0 || tablica[i][j+1] == 3){
                            tablica[i][j+1] = tablica[i][j] + 1;
                            liczba_zmian++;
                        }
                    }

                }
            }
        }
    }
    //wypisz_tablice(szerokosc, wysokosc, tablica);

}

void znajdz_sciezke (int **tablica, int szerokosc, int wysokosc, int x_koniec, int y_koniec, int x, int y){
    int liczba_krokow = 0;
    char kierunek = 'N';

    //wybór kierunku początkowego
    if (x == 0){
        kierunek = 'E';
    } else if (y == 0){
        kierunek = 'S';
    } else if (x == szerokosc-1){
        kierunek = 'W';
    } else if (y == wysokosc-1){
        kierunek = 'N';
    } else{
        //sprawdzenie z której strony jest wolne pole
        if (tablica[x+1][y] != 1){
            kierunek = 'E';
        } else if (tablica[x-1][y] != 1){
            kierunek = 'W';
        } else if (tablica[x][y+1] != 1){
            kierunek = 'S';
        } else if (tablica[x][y-1] != 1){
            kierunek = 'N';
        } else {
            printf("Ups, coś poszło nie tak\n");
        }
    }
    
    printf("Kierunek początkowy to %c\n", kierunek);

    int x_start = x;
    int y_start = y;

    x = x_koniec;
    y = y_koniec;

    int historia_krokow[szerokosc*wysokosc]; //liczby > 0 to liczba kroków; -1 skręt w lewo; -2 skręt w prawo
    for (int i = 0; i < szerokosc*wysokosc; i++){
        historia_krokow[i] = 0;
    }

    int licznik = 0;

    //wybór kierunku końcowego
    if (x == 0){
        kierunek = 'E';
    } else if (y == 0){
        kierunek = 'S';
    } else if (x == szerokosc-1){
        kierunek = 'W';
    } else if (y == wysokosc-1){
        kierunek = 'N';
    } else{
        //sprawdzenie z której strony jest wolne pole
        if (tablica[x+1][y] >= 10){
            kierunek = 'E';
        } else if (tablica[x-1][y] >= 10){
            kierunek = 'W';
        } else if (tablica[x][y+1] >= 10){
            kierunek = 'S';
        } else if (tablica[x][y-1] >= 10){
            kierunek = 'N';
        } else {
            printf("Ups, coś poszło nie tak\n");
        }
    }

    //printf("Kierunek końcowy to %c\n", kierunek);

    while (x != x_start || y != y_start){
        if (kierunek == 'W'){
            if (tablica[x-1][y] == tablica[x][y] -1){
                liczba_krokow++;
                x--;
                historia_krokow[licznik] = liczba_krokow;
            }else if (tablica[x][y-1] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -1;
                licznik++;
                liczba_krokow=1;
                kierunek = 'N';
                y--;
            } else if (tablica[x][y+1] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -2;
                licznik++;
                liczba_krokow=1;
                kierunek = 'S';
                y++;
            } 
        }

        if (kierunek == 'E'){
            if (tablica[x+1][y] == tablica[x][y] -1){
                liczba_krokow++;
                x++;
                historia_krokow[licznik] = liczba_krokow;
            }else if (tablica[x][y-1] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -2;
                licznik++;
                liczba_krokow=1;
                kierunek = 'N';
                y--;
            } else if (tablica[x][y+1] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -1;
                licznik++;
                liczba_krokow=1;
                kierunek = 'S';
                y++;
            } 
        }

        if (kierunek == 'N'){
            if (tablica[x][y-1] == tablica[x][y] -1){
                liczba_krokow++;
                y--;
                historia_krokow[licznik] = liczba_krokow;
            }else if (tablica[x-1][y] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -2;
                licznik++;
                liczba_krokow=1;
                kierunek = 'W';
                x--;
            } else if (tablica[x+1][y] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -1;
                licznik++;
                liczba_krokow=1;
                kierunek = 'E';
                x++;
            } 
        }

        if (kierunek == 'S'){
            if (tablica[x][y+1] == tablica[x][y] -1){
                liczba_krokow++;
                y++;
                historia_krokow[licznik] = liczba_krokow;
            }else if (tablica[x-1][y] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -1;
                licznik++;
                liczba_krokow=1;
                kierunek = 'W';
                x--;
            } else if (tablica[x+1][y] == tablica[x][y] -1){
                licznik++;
                historia_krokow[licznik] = -2;
                licznik++;
                liczba_krokow=1;
                kierunek = 'E';
                x++;
            } 
        }

    }
    //printf("Liczba kroków: %d\n", liczba_krokow);
    if (liczba_krokow>0){
        printf("Forward %d\n", liczba_krokow);
    }
    for (int i = szerokosc*wysokosc-1; i >= 0; i--){
        if (historia_krokow[i] > 0){
            printf("Forward %d\n", historia_krokow[i]);
        } else if (historia_krokow[i] == -1){
            printf("Turn left\n");
        } else if (historia_krokow[i] == -2){
            printf("Turn right\n");
        }
    }
    printf("Koniec\n");
}


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

    //wypisz_tablice(szerokosc, wysokosc, tablica);
    //printf("\n");

    oznaczanie_pol(tablica, szerokosc, wysokosc, x_koniec, y_koniec, x, y);
    znajdz_sciezke(tablica, szerokosc, wysokosc, x_koniec, y_koniec, x, y);


    //wypisz_tablice(szerokosc, wysokosc, tablica);
    //getchar();


    return 0;
}