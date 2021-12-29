#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RED       "\033[31m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define RESET     "\033[34m"
#define GREEN     "\033[0;32m"

void inv();
int determinante();
void result();
void input(char y[], int qual);
int stoi(char *x);
int validaEquacao2(char x[]);
void logeq2();

static int pos[2], posn = 0, I[2][2], U[2], h = 0;
static long double x[2][2], a[1][2];

int equacao2(){

    system("clear");
    char string[100];
    
    printf("============================================================\n");
    printf("|"GREEN"------------------Exemplo: 23.i1-06.i2=1------------------"RESET"|\n");
    printf("============================================================\n");

    //inserindo as equacoes;
    for (int i = 0; i < 2; i++)
    {
        int valida = 0;
        while (valida == 0)//enquanto valida for 0;
        {
            printf("Informe a equacao - %d: ", i+1);
            fgets(string, sizeof(string)-2, stdin);
            
            valida = validaEquacao2(string);//verifica erros em string se não encontrar erros retorna 1;
        }
        input(string, i);
    
    }
 

    //Calculo de determinante;
    determinante();

    //Calcula Matriz inversa;
    inv();

    printf("\nResultado:\n");
    result();   
    logeq2();
}

void logeq2(){

    FILE *pfile;

    pfile = fopen("Log_eq2.txt", "a");
    if (pfile == NULL)
    {
        perror("Erro");
        clearerr(pfile);
    }

    //matriz Correntes;
    fprintf(pfile, "\n Matriz Corrente\n");
    for (int x = 0; x < 2; x++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(pfile, "\t\t\t\t%d", I[x][j]);
        }
        fprintf(pfile, "\n");
    }
    fprintf(pfile, "\n");

    //matriz Tensoes;
    fprintf(pfile, "\n Matriz Tensão\n");
    for (int x = 0; x < 2; x++)
    {
        fprintf(pfile, "\t\t\t\t%d", U[x]);
        fprintf(pfile, "\n");
    } 

    //determinante;
    fprintf(pfile, "\n Determinante: %d\n", determinante());

    //Inversa matriz Correntes;
    fprintf(pfile, "\n Matriz Inversa\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(pfile, "\t\t\t\t%Lf", x[i][j]);
        }
        fprintf(pfile, "\n");
    }
    
    fprintf(pfile, "\n");

    //resultado;
    for (int i = 0; i < 2; i++)
    {
        fprintf(pfile," Corrente %d = %Lf\n", i+1, a[0][i]);
    }

    fprintf(pfile, "-------------------------------------");
    fprintf(pfile, "\n");
    fclose(pfile);   

}

int validaEquacao2(char x[]){

    int tamanho = 0, ponto = 0, sinal = 0;
    tamanho = strlen(x);
    
    for (int i = 0; i < tamanho; i++)
    {
        //verifica se há tensão;
        if (x[i] == '=' && tamanho < i+3){
            printf("Equação invalida, nada depois de '='!\n");
            return 0;            
        }

        //conta a quantidade de pontos;
        if (x[i] == '.' && x[i+1] != '.' && x[i-1] != '.')
        {
            ponto++;
        }     

        //testa se há pontos juntos;
        if (x[i] == '.' && (x[i+1] == '.' || x[i] != '.'))
        {
            printf("Equação invalida!\n");
            return 0;
        }
        
        //conta a quantidade dos sinais;
        if (x[i] == '+' || x[i] == '-')
        {
            sinal++;
        }
       
        //procura por espaços;
        if (x[i] == ' ')
        {
            printf("Equação invalida, não coloque espaço!\n");
            return 0;
        }
        
    }

    //verifica se a quantidade de ponto achado é igual a 2;
    if (ponto != 2)
    {
        printf("Equação invalida, Lembrese do '.'!\n");
        return 0;
    }

    //verifica se a quantidade de sinal menor 3 maior 1;
    if (sinal > 3)
    {
        printf("Equação invalida, erro com sinais(+-)!\n");
        return 0;
    }
    
    //verifica se o codigo é muito pequeno ou muito grande;
    if (tamanho <= 11 || tamanho >=  21)
    {
        printf("Equação invalida, divergencia no tamanho!\n");
        return 0;
    }
    return 1;

}

//calcula a determinante;
int determinante()
{  
   return (I[1][1]*I[0][0])-(I[1][0]*I[0][1]);
}

//inverte a matriz;
void inv()
{
    float temp[2][2], det = determinante();
    //etapa 1
    for (int k = 0; k < 2; k++)
    {
        for (int j = 0; j < 2; j++)
        {
            temp[k][j] = I[k][j]/det;
        }
    }
    //etapa 2:
    x[0][0] = temp[1][1];
    x[1][1] = temp[0][0];
    x[0][1] = (temp[0][1]*-1);
    x[1][0] = (temp[1][0]*-1);
}

void result()
{
    a[0][0] = (x[0][0] * U[0]) + (x[0][1]*U[1]);
    a[0][1] = (x[1][0] * U[0]) + (x[1][1]*U[1]);  

    for (int i = 0; i < 2; i++)
    {
        printf("\tCorrente %d = %Lf\n", i+1, a[0][i]);
    }

    printf("\n");
}

void input(char y[], int qual)
{
    //contador que define I:1,2,3 na matriz;
    int contador = 0, semsinal = 0;

    //roda por toda a string
    for (int i = 0; i < strlen(y); i++)
    {
        //procura por .
        if(y[i] == '.')
        {
            pos[0] = i;//declara onde achou;
            contador++;//contador que define I:1,2,3 na matriz;

            //conta quantas cassas até o sinal;
            for (int j = 0; j < 5; j++)
            {
                if (y[i-j] == '+' || y[i-j] == '-')
                {
                    //define quantidade de casas;
                    pos[1] = j;
                }else if (i-j == 0)//se for a posição 0 da string;
                {
                    pos[1] = j;//define a posição;
                    semsinal = 1;//se o numero não começou com + ou -;
                    break;
                }
            }

            posn = pos[0] - pos[1];//define a posição incial do que achou;

            //inicializa variavel temporaria que armazena char que será transformado em int;
            char temp[pos[1]+1];

            if (semsinal == 1)//se for sem sinal;
            {
                temp[0] = '+'; //coloca um + na primeira posição;
                int contador = 0;//imicializa contador;

                while(contador < pos[1])//enquanto contador menor que pos[1];
                {
                    temp[contador+1] = y[contador];//temp quecebe partindo de 1;
                    contador++;
                }
                temp[pos[1]+1] = '\0';//fecha a temp;
                semsinal = 0;
                
            }else //caso não seja sem o sinal;
            {
                //define com as posições que achou;
                for (int k = posn; k <= posn + pos[1]; k++)
                {
                    temp[k-posn] = y[k];
                }

                temp[pos[1]] = '\0';
            }

            //transforma de sting para int;
            I[qual][contador-1] = stoi(temp);

        }

        //procura por '=';
        if (y[i] == '=')
        { 
            //h recebe a posição onde achou o '=' + 1;
            h = i+1; 
            
            //se não começou com + ou -;
            if (y[h] != '+' && y[h] != '-'){
                
                //define o inicio em '=';
                h = i;
            }

            //marcador guardara o tamanho do char que chegou
            int marcador = (strlen(y)-h)-1;

            //inicializa variavel que armazena char que será transformado em int;
            char x[marcador];

            //define x;
            for (int j = 0; j < marcador; j++)
            {
                //printf("\n temp[%d] = %c\n", j, y[i+j]);
                x[j] = y[h+j];

            }

            //redefine o final da string;
            x[marcador] = '\0';

            //chama stoi(x), para transformar em int[];
            U[qual] = stoi(x);
        }
        
    }    

}
