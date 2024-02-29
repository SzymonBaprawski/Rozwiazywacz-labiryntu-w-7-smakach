#ifndef WCZYTANIE_Z_PLIKU_H
#define WCZYTANIE_Z_PLIKU_H

int sprawdz_szerokosc (char *nazwa_pliku);

int sprawdz_wysokosc (char *nazwa_pliku);

void alokuj_pamiec (int szerokosc, int wysokosc, int ***tablica);

void wczytaj_z_pliku (char *nazwa_pliku, int szerokosc, int wysokosc, int **tablica);

void wypisz_tablice (int szerokosc, int wysokosc, int **tablica);

#endif // WCZYTANIE_Z_PLIKU_H
