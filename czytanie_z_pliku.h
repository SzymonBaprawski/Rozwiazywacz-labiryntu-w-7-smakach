#ifndef CZYTANIE_Z_PLIKU_H
#define CZYTANIE_Z_PLIKU_H

#include <stdio.h>
#include <stdlib.h>

typedef struct maze{
    int m; //ilosc wierszy
    int n; //ilosc kolumn
    int maz[2049][2049]; //labirynt wypelniony "0"-> pusta kratka () ; "1"->sciana(X); "2"-> poczatek (P); "3"-> koniec (K)  
}maze;

maze* returnmaze(FILE* plik);

#endif

/*int main(int argc, char ** argv)
{
        FILE* in = argc >1 ? fopen(argv[1], "r"):NULL;

    if(in == NULL)
    {
        fprintf(stderr, "zly input lub nie moge otworzyc");
        return 1;
    }

        maze * lab = returnmaze(in);

        for( int i = 0; i < lab->m ; i++)
        {
                for(int j = 0; j< lab->n; j++)
                {
                        printf("%d", lab->maz[j][i]);
                }
        printf("\n");
        }

        free(lab);
        return 0;
}*/