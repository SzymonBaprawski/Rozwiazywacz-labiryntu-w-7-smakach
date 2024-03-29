#include "czytanie_z_pliku.h"
#include "Bruteforce.h"

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

void forward(int kierunek)
{
    switch(kierunek){

        case 0:
            p.w--;
            break;

        case 1:
            p.k++;
            break;

        case 2:
            p.w++;
            break;

        case 3:
            p.k--;
            break;
    }
    p.f++;
}

int sum(int a, int b, int c, int d)
{
    int sum = 0; 
    sum = a+b+c+d;
    return sum;
}

void turnR()
{
    if(p.f != 0)
    printf("FORWARD %d\n", p.f);

    printf("TURNRIGHT\n");
    p.kierunek ++;
    if(p.kierunek == 4)
        p.kierunek = 0;

    if(p.f != 0 )
        p.f=0;
}   

void turnL()
{
    if(p.f != 0)
    printf("FORWARD %d\n", p.f);

    printf("TURNLEFT\n");
    p.kierunek --;
    if(p.kierunek == -1)
        p.kierunek = 3;

    if(p.f != 0 )
        p.f=0;
}

int main(int argc, char ** argv)
{
    FILE* in = argc >1 ? fopen(argv[1], "r"):NULL;

    if(in == NULL)
    {
        fprintf(stderr, "zly input lub nie moge otworzyc");
        return 1;
    }

    p.f = 0;

    srand(time(NULL));

    maze* lab = returnmaze(in);

    for(int i = 0; i < lab->m;i++)
    {
        if(lab->maz[0][i] == 2)
        {
            p.k = 1;
            p.w = i;
            p.kierunek = 1;
            printf("START\n");
            lab->maz[0][i] = 1;
            if (lab->maz[2][1] == 1)
            {
                turnR;
                p.kierunek --;
                printf("%d\n" ,p.kierunek);
            }else if(lab->maz[1][2] == 1)
            {
                forward(p.kierunek);
            }else{
                forward(p.kierunek);
            }
        }
    }
    while(lab->maz[p.k+1][p.w] != 6)
    {
        if(lab->maz[p.k][p.w] == 1)
        {
            printf("jestem w scianie\n");
            return 1;
        }
        if(p.kierunek < 0 || p.kierunek > 3)
        {
            printf("nie tak sie kreci dzieciak\n");
            return 1;
        }

        int suma = sum(lab->maz[p.k][p.w - 1], lab->maz[p.k+1][p.w], lab->maz[p.k][p.w +1], lab->maz[p.k - 1][p.w]);
        int kod[4];
        kod[0] = lab->maz[p.k][p.w-1];
        kod[1] = lab->maz[p.k+1][p.w];
        kod[2] = lab->maz[p.k][p.w +1];
        kod[3] = lab->maz[p.k - 1][p.w];

        if(suma == 2)// korytaz
        {
            if(kod[0] == 1 && kod[1]==1)
            {
                if(p.kierunek == 1){
                    turnR();
                    forward(p.kierunek);
                }else{
                    turnL();
                    forward(p.kierunek);
                }
            }else if(kod[0] == 1 && kod[2] == 1){
                forward(p.kierunek);
            }else if(kod[0] == 1 && kod[3] == 1){
                if(p.kierunek == 0){
                    turnR();
                    forward(p.kierunek);
                }else{
                    turnL();
                    forward(p.kierunek);
                }
            }else if(kod[1] == 1 && kod[2] == 1){
                if(p.kierunek == 2){
                    turnR();
                    forward(p.kierunek);
                }else{
                    turnL();
                    forward(p.kierunek);
                }
            }else if(kod[1] == 1 && kod[3] == 1){
                forward(p.kierunek);
            }else {
                if(p.kierunek == 3){
                    turnR();
                    forward(p.kierunek);
                }else{
                    turnL();
                    forward(p.kierunek);
                }
            }
        }else if(suma == 1)//nood
        {
            if(kod[0] == 1)
            {
                switch(p.kierunek){

                    case 1:
                        int r = rand() % 2 + 1;
                        if(r==1){
                            forward(p.kierunek);
                        }else{
                            turnR();
                            forward(p.kierunek);
                        }
                    break;

                    case 0:
                        r = rand() % 2 + 1;
                        if(r==1){
                            turnR();
                            forward(p.kierunek);
                        }else{
                            turnL();
                            forward(p.kierunek);
                        }
                    break;

                    case 3:
                        r = rand() % 2 + 1;
                        if(r==1){
                            forward(p.kierunek);
                        }else{
                            turnL();
                            forward(p.kierunek);
                        }
                    break;
                }
            }else if(kod[1] == 1)
            {
                switch(p.kierunek){

                    case 2:
                        int r = rand() % 2 + 1;
                        if(r==1){
                            forward(p.kierunek);
                        }else{
                            turnR();
                            forward(p.kierunek);
                        }
                    break;

                    case 0:
                        r = rand() % 2 + 1;
                        if(r==1){
                            forward(p.kierunek);
                        }else{
                            turnL();
                            forward(p.kierunek);
                        }
                    break;
                     
                    case 1:
                        r = rand() % 2 + 1;
                        if(r==1){
                            turnL();
                            forward(p.kierunek);
                        }else{
                            turnR();
                            forward(p.kierunek);
                        }
                    break;
                }
            }else if(kod[2] == 1)
            {
                switch(p.kierunek){

                    case 1:
                        int r = rand() % 2 + 1;
                        if(r==1){
                            forward(p.kierunek);
                        }else{
                            turnL();
                            forward(p.kierunek);
                        }
                    break;

                    case 3:
                        r = rand() % 2 + 1;
                        if(r==1){
                            turnR();
                            forward(p.kierunek);
                        }else{
                            forward(p.kierunek);
                        }
                    break;

                    case 2:
                        r = rand() % 2 + 1;
                        if(r==1){
                            turnR();
                            forward(p.kierunek);
                        }else{
                            turnL();
                            forward(p.kierunek);
                        }
                    break;
                }
            }else
            {
                switch(p.kierunek){

                    case 0:
                        int r = rand() % 2 + 1;
                        if(r==1){
                            forward(p.kierunek);
                        }else{
                            turnR();
                            forward(p.kierunek);
                        }
                    break;

                    case 3:
                        r = rand() % 2 + 1;
                        if(r==1){
                            turnR();
                            forward(p.kierunek);
                        }else{
                            turnL();
                            forward(p.kierunek);
                        }
                    break;

                    case 2:
                        r = rand() % 2 + 1;
                        if(r==1){
                            turnL();
                            forward(p.kierunek);
                        }else{
                            forward(p.kierunek);
                        }
                    break;
                }
            }
        }else if(suma == 3)//slepa uliczka
        {
            turnR();
            turnR();
            forward(p.kierunek);
      
        } else if (suma == 0)
        {
            int r = rand() % 3 + 1;

                if(r==1){
                    turnL();
                    forward(p.kierunek);
                }else if(r == 2){
                    forward(p.kierunek);
                }else{
                    turnR();
                    forward(p.kierunek);
                }
            
        }
        

    }
    
    if(p.kierunek == 2)
    {

        turnL();
        printf("FORWARD 1\n KONIEC\n");
    }else{
       printf("FORWARD %d\n KONIEC\n", p.f+1);
    }

    free(lab);
    return 0;
}