#include "DFS.h"


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

int sum(int a, int b, int c, int d)
{
    int sum = 0; 
    sum = a+b+c+d;
    return sum;
}

void push(stos_type **top, int k, int w, int kierunek, int* trasa) {

    if(*top==NULL) {
        *top=(stos_type *) malloc (sizeof(stos_type));
        (*top)->kolumna=k;
        (*top)->wiersz = w;
        (*top)->kierunek = kierunek;
        (*top)->trasa = trasa;
        (*top)->ile =0;
        (*top)->next=NULL;
    }else {
        stos_type *nowy;
        nowy=(stos_type *)malloc(sizeof(stos_type));
        nowy->kolumna=k;
        nowy->wiersz = w;
        nowy->kierunek = kierunek;
        nowy->trasa = trasa;
        nowy->ile =0;
        nowy->next=*top;
        *top=nowy;
    }
}

void pop(stos_type **top) {
 
    if (*top==NULL) {
        printf("\nSTACK UNDERFLOW!! Nie ma czego zdjac ze stosu.");
    }else {
        stos_type * tmp=NULL;
        tmp=(*top)->next;
        free(*top);
        *top=tmp;
    }
}

void daj(stos_type *top) {

    if(top==NULL) printf("List is empty");
    else {
        stos_type *current=top;
            p.k = current->kolumna;
            p.w = current->wiersz;
            p.kierunek = current->kierunek;
    }
}

void turnR(){
    p.kierunek ++;
    if(p.kierunek == 4)
        p.kierunek = 0;
}

void turnL(){
    p.kierunek --;
    if(p.kierunek == -1)
        p.kierunek = 3;
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
}


    int dlugosc = 0;
    int trasa[1000];


int main(int argc, char** argv)
{
    FILE* in = argc >1 ? fopen(argv[1], "r"):NULL;

    if(in == NULL)
    {
        fprintf(stderr, "zly input lub nie moge otworzyc");
        return 1;
    }

    maze* lab = returnmaze(in);

    
    stos_type *top;
    top=NULL;

    if(lab->maz[2][1] == 1){
        //printf(" START \nFORWARD 1\n TURNRIGHT\n FORWARD 1\n");
        lab->maz[0][1] = 1;
        p.kierunek = 2;
        p.k = 1;
        p.w = 2;
        push(&top, p.k, p.w, p.kierunek, trasa);
    }else if (lab->maz[1][2] == 1){
       // printf(" START \nFORWARD 2\n");
        lab->maz[0][1] = 1;
        p.kierunek = 1;
        p.k = 2;
        p.w = 1;
        push(&top, p.k, p.w, p.kierunek, trasa);
    }else{  
        //printf(" START \nFORWARD 1\n");
        lab->maz[0][1] = 0;
        p.kierunek = 1;
        p.k = 1;
        p.w = 1;
        push(&top, p.k, p.w, p.kierunek, trasa);
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

         printf("koluna %d, wiersz %d, kierunek %d\n ", p.k, p.w, p.kierunek);

        if(suma == 2)
        {
            if(kod[0] == 1 && kod[1]==1)
            {
                if(p.kierunek == 1){
                    trasa[dlugosc] = -1; // prawo
                    dlugosc++;
                    turnR();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }else{
                    trasa[dlugosc] = -2; // lewo
                    dlugosc++;
                    turnL();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }
            }else if(kod[0] == 1 && kod[2] == 1){
                trasa[dlugosc] = 1;
                dlugosc++;
                forward(p.kierunek);
            }else if(kod[0] == 1 && kod[3] == 1){
                if(p.kierunek == 0){
                    trasa[dlugosc] = -1; // prawo
                    dlugosc++;
                    turnR();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }else{
                    trasa[dlugosc] = -2; // lewo
                    dlugosc++;
                    turnL();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }
            }else if(kod[1] == 1 && kod[2] == 1){
                if(p.kierunek == 2){
                    trasa[dlugosc] = -1; // prawo
                    dlugosc++;
                    turnR();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }else{
                    trasa[dlugosc] = -2; // lewo
                    dlugosc++;
                    turnL();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }
            }else if(kod[1] == 1 && kod[3] == 1){
                trasa[dlugosc] = 1;
                dlugosc++;
                forward(p.kierunek);
            }else {
                if(p.kierunek == 3){
                    trasa[dlugosc] = -1; // prawo
                    dlugosc++;
                    turnR();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }else{
                    trasa[dlugosc] = -2; // lewo
                    dlugosc++;
                    turnL();
                    trasa[dlugosc] = 1; // prosto
                    dlugosc++;
                    forward(p.kierunek);
                }
            }
        }else if(suma == 1) 
        {
            if(top->kolumna != p.k || top->wiersz != p.w){
            top->ile++;
            push(&top, p.k, p.w, p.kierunek, trasa);
            }

            if( top->ile == 1)
            {
                switch(p.kierunek){
                    case 0:
                        if(kod[3] == 0 && kod[0]==0)
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = -1; // prawo
                            dlugosc++;
                            turnR();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;

                    case 1:
                        if(kod[0] == 0 && kod[1]==0)
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = -1; // prawo
                            dlugosc++;
                            turnR();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;

                    case 2:
                        if(kod[1] == 0 && kod[2] == 0)
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = -1; // prawo
                            dlugosc++;
                            turnR();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;

                    case 3:
                        if(kod[2] == 0 && kod[3] == 0)
                   {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = -1; // prawo
                            dlugosc++;
                            turnR();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;  
                }
            }else if(top->ile == 2)
            {   
                
                pop(&top);
                p.k = top->kolumna;
                p.w = top->wiersz;
                p.kierunek = top->kierunek;

            }else
            {

                for( int i = 0; i < dlugosc; i++)
                {
                    trasa[i]=0;
                }

                dlugosc = 0;

                switch(p.kierunek){
                    case 0:
                        if(kod[3] == 0)
                        {
                            trasa[dlugosc] = -2; // lewo
                            dlugosc++;
                            turnL();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;

                    case 1:
                        if(kod[0] == 0)
                        {
                            trasa[dlugosc] = -2; // lewo
                            dlugosc++;
                            turnL();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;

                    case 2:
                        if(kod[1] == 0)
                        {
                            trasa[dlugosc] = -2; // lewo
                            dlugosc++;
                            turnL();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;

                    case 3:
                        if(kod[2] == 0)
                        {
                            trasa[dlugosc] = -2; // lewo
                            dlugosc++;
                            turnL();
                            trasa[dlugosc] = 1; // prosto
                            dlugosc++;
                            forward(p.kierunek);
                        }else
                        {
                            trasa[dlugosc] = 1;
                            dlugosc++;
                            forward(p.kierunek);
                        }
                    break;  
                }

            }
        }else if (suma== 3)
          {
            daj(top);
            top->ile++;
        
            for( int i = 0; i < dlugosc; i++)
            {
                trasa[i]=0;
            }

            dlugosc = 0;
        }  else if (suma == 0)
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
       /* int tmpf =0;
        while( top !=NULL) 
        {
            int i =0;
            while (top->trasa[i] == 1 || top->trasa[i] == -1 || top->trasa[i] == -2)
            {
                switch(top->trasa[i]){
                case 1:
                    tmpf ++;
                break;

                case -1:
                    if(tmpf != 0){
                        printf("FORWARD %d\n", tmpf);
                    }
                    tmpf = 0;
                    printf("TURNRIGHT\n");
                break;

                case -2:
                    if(tmpf != 0){
                        printf("FORWARD %d\n", tmpf);
                    }
                    tmpf = 0;
                    printf("TURNLEFT\n");
                break;
                }
                i++;
            }
            

            pop(&top);
        }

        /*for(int i = 0; i < dlugosc; i++)
        {
            switch(trasa[i]){
                case 1:
                    tmpf ++;
                break;

                case -1:
                    if(tmpf != 0){
                        printf("FORWARD %d\n", tmpf);
                    }
                    tmpf = 0;
                    printf("TURNRIGHT\n");
                break;

                case -2:
                    if(tmpf != 0){
                        printf("FORWARD %d\n", tmpf);
                    }
                    tmpf = 0;
                    printf("TURNLEFT\n");
                break;
                }
            }*/
           /* if(p.kierunek == 1)
            {
                printf("FORWARD 1 \n KONIEC \n");
            }else{
                printf("TURNLEFT \n FORWARD 1\n KONIEC\n");
            }
            */
            printf(" SUKCES KONIEC\n");
    free(lab);
    return 0;
}