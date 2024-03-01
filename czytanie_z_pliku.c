#include "czytanie_z_pliku.h"

maze* returnmaze(FILE* plik) //nalzey podac otwarty do czytania plik "r"
{
    maze* dane = malloc(sizeof *dane);

    int tmp= 0;
    int i = 0;
    dane->m = 0;

    while(tmp != EOF)
    {
        tmp = fgetc(plik);
        switch (tmp)
        {
                case 'X':
                dane->maz[i][dane->m] = 1;
                i++;
                break;

                case ' ':
                dane->maz[i][dane->m] = 0;
                i++;
                break;

                case '\n':
                i = 0;
                dane->m++;
                break;

                case 'P':
                dane->maz[i][dane->m] = 2;
                i++;
                break;

                case 'K':
                dane->maz[i][dane->m] = 6;
                dane->n = i; // to nie dziala kiedy K nie jest w dolnym prawym roku labiryntu !!!
                i++;
                break;

            }
               }
    dane->m--;
    dane->n++;

    fclose(plik);

    return dane;
}
