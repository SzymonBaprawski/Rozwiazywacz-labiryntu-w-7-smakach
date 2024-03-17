#ifndef WCZYTANIE_Z_PLIKU_H
#define WCZYTANIE_Z_PLIKU_H

int sprawdz_szerokosc (char *nazwa_pliku);

int sprawdz_wysokosc (char *nazwa_pliku);

void alokuj_pamiec (int szerokosc, int wysokosc, int ***tablica);

void wczytaj_z_pliku (char *nazwa_pliku, int szerokosc, int wysokosc, int **tablica);

void wypisz_tablice (int szerokosc, int wysokosc, int **tablica);

void znajdz_start (int szerokosc, int wysokosc, int **tablica, int *x_start, int *y_start);

void znajdz_koniec (int szerokosc, int wysokosc, int **tablica, int *x_koniec, int *y_koniec);

void rozszerz_pamiec (int szerokosc, int wysokosc, int ***tablica);

#endif // WCZYTANIE_Z_PLIKU_H
