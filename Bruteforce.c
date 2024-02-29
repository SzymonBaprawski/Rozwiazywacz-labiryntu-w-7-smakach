#include "czytanie_z_pliku.h"

struct p{
    int w;
    int k;
    char kierunek; // "G", "P", "D", "L"
}p;

void forward(char kierunek)
{
    switch(kierunek){

        case 'G':
            p.w--;
            break;

        case 'P':
            p.k++;
            break;

        case 'D':
            p.w++;
            break;

        case 'L':
            p.k--;
            break;
    }
}

int sum(int a, int b, int c, int d)
{
    int sum = 0; 
    sum = a+b+c+d;
    return sum;
}

int main(int argc, char ** argv)
{
    FILE* in = argc >1 ? fopen(argv[1], "r"):NULL;

    if(in == NULL)
    {
        fprintf(stderr, "zly input lub nie moge otworzyc");
        return 1;
    }

    maze * lab = returnmaze(in);

    for(int i = 0; i < lab->m;i++)
    {
        if(lab->maz[0][i] == 2)
        {
            int kolumna = 1;
            int wiersz = i;
            printf("START\n");
            printf("FORWARD 1\n");
            lab->maz[0][i] =-5;
        }
    }

    while(lab->maz[p.k][p.w] != 3)
    {
        if(lab->maz[p.k][p.w] == 1)
        {
            printf("jestem w scianie\n");
            return 1;
        }

        int suma = sum(lab->maz[p.k][p.w - 1], lab->maz[p.k+1][p.w], lab->maz[p.k][p.w +1], lab->maz[p.k - 1][p.w]);

        if(suma == 2)// forward
        {

        }else if(suma == 1)//nood
        {

        }else if(suma == 3)//slepa uliczka
        {
            
        }else if(suma < 0) //poczatek ?
        {

        }
    }

    free(lab);
    return 0;
}