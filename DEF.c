#include <stdio.h>
#include <stdlib.h>
#include "wczytywanie_z_pliku.h"

void follower (int **tablica, int szerokosc, int wysokosc, int x_koniec, int y_koniec, int x, int y){
    int liczba_krokow = 0;

    char kierunek = 'E';

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

    while (x!=x_koniec || y!=y_koniec){
        //printf("Kierunek: %c, x: %d, y: %d\n", kierunek, x, y);
        if (kierunek == 'E'){
            if (y > 0 && tablica[x][y-1] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn left\n");
                kierunek = 'N';
                y--;
                liczba_krokow = 1;
            } else if (x < szerokosc && tablica[x+1][y] != 1){
                x++;
                liczba_krokow++;
            } else if (y < wysokosc && tablica[x][y+1] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn right\n");
                kierunek = 'S';
                y++;
                liczba_krokow = 1;
            } else if (x > 0 && tablica[x-1][y] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn around\n");
                kierunek = 'W';
                x--;
                liczba_krokow = 1;
                
            }
        }

        else if (kierunek == 'W'){
            if (y > 0 && tablica[x][y+1] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn left\n");
                kierunek = 'S';
                y++;
                liczba_krokow = 1;
            } else if (x > 0 && tablica[x-1][y] != 1){
                x--;
                liczba_krokow++;
            } else if (y > 0 && tablica[x][y-1] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn right\n");
                kierunek = 'N';
                y--;
                liczba_krokow = 1;
            } else if (x < szerokosc && tablica[x+1][y] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn around\n");
                kierunek = 'E';
                x++;
                liczba_krokow = 1;
                
            }
        }

        else if (kierunek == 'N'){
            if (x > 0 && tablica[x-1][y] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn left\n");
                kierunek = 'W';
                x--;
                liczba_krokow = 1;
            } else if (y > 0 && tablica[x][y-1] != 1){
                y--;
                liczba_krokow++;
            } else if (x < szerokosc && tablica[x+1][y] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn right\n");
                kierunek = 'E';
                x++;
                liczba_krokow = 1;
            } else if (y > 0 && tablica[x][y+1] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn around\n");
                kierunek = 'S';
                y++;
                liczba_krokow = 1;
                
            }
        }


        else if (kierunek == 'S'){
            if (x < szerokosc && tablica[x+1][y] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn left\n");
                kierunek = 'E';
                x++;
                liczba_krokow = 1;
            } else if (y < wysokosc && tablica[x][y+1] != 1){
                y++;
                liczba_krokow++;
            } else if (x > 0 && tablica[x-1][y] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn right\n");
                kierunek = 'W';
                x--;
                liczba_krokow = 1;
            } else if (y < wysokosc && tablica[x][y-1] != 1){
                printf("Forward %d\n", liczba_krokow);
                printf("Turn around\n");
                kierunek = 'N';
                y--;
                liczba_krokow = 1;
                
            }
        }
        //printf("Kierunek: %c, x: %d, y: %d\n", kierunek, x, y);
        //getchar();

    }
    printf("Forward %d\n", liczba_krokow);

    if (x == x_koniec && y == y_koniec){
        printf("Koniec\n");
    } else {
        printf("Ups, coś poszło BARDZO nie tak\n");
    }

    //printf("%d %d ; %d %d\n", x, y, x_koniec, y_koniec);
}

void flood(int **tablica, int szerokosc, int wysokosc){
    int liczba_zmian = 1;
    int otaczajace = 0;

    while (liczba_zmian > 0){
        liczba_zmian = 0;
        for (int i = 1; i < szerokosc-1; i++){
            for (int j = 1; j < wysokosc-1; j++){
                if (tablica[i][j] == 0){
                    otaczajace = 0;
                    if (tablica[i-1][j] == 1){
                        otaczajace++;
                    }
                    if (tablica[i+1][j] == 1){
                        otaczajace++;
                    }
                    if (tablica[i][j-1] == 1){
                        otaczajace++;
                    }
                    if (tablica[i][j+1] == 1){
                        otaczajace++;
                    }
                    if (otaczajace >= 3){
                        tablica[i][j] = 1;
                        liczba_zmian++;
                    }
                }
            }
        }
    }
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

   // wypisz_tablice(szerokosc, wysokosc, tablica);
    //getchar();
    flood(tablica, szerokosc, wysokosc);
    //getchar();
    //wypisz_tablice(szerokosc, wysokosc, tablica);
    //getchar();

    follower(tablica, szerokosc, wysokosc, x_koniec, y_koniec, x, y);

    return 0;
}