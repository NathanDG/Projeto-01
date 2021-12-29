#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

#define RED       "\033[31m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define RESET     "\033[34m"
#define GREEN     "\033[0;32m"

//declara as funções
void input3(char y[], int qual);
int stoi3(char x[]);
int determinante3();
void inv3();
void result3();
int validaEquacao(char x[]);
void log3();

static char equacao[30];

//I[equacao1,2,3,][I1,2,3], u[equacao];
static int pos[2], posn = 0, I[3][3], U[3], h = 0;
//variaveis para calculo de determinante;
static int dp=0, ds=0, dr=0, det=0;
//variaveis para multiplicação de matrizes;
static long double x[3][3], a[3][1], d[3][3];

int equacao3(){

    char equacao[100];
    system("clear");
    //inserindo as equacoes;
    printf("============================================================\n");
    printf("|"GREEN"---------------Exemplo: -1.i1+2.i2-23.i3=+0---------------"RESET"|\n");
    printf("============================================================\n");

    //insirindo as equações;
    for (int i = 0; i < 3; i++)
    {
        int valida = 0;//varivel que define se equacao é valido;
        while (valida == 0)//enquanto equacao não for valida;
        {
            printf("Informe a equacao - %d: ", i+1);
            fgets(equacao, sizeof(equacao)-2, stdin);
            
            valida = validaEquacao(equacao);//testa se equacao é valida e armazena em valida;
        }
        input3(equacao, i);//chama a função que captura os dados da string;
       
    }

    //calcula o determinante
    determinante3();

    //inverte a matriz
    inv3();

    printf("\nResultado:");
    result3(); 
    log3();
}

void log3(){

    FILE *pfile;

    pfile = fopen("Log_eq3.txt", "a");
    if (pfile == NULL)
    {
        perror("Erro");
        clearerr(pfile);
    }

    //Imprimindo no Log A Matriz I;
    fprintf(pfile, "\n\nMatriz Corrente:\n");
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            fprintf(pfile, "\t\t\t\t%d", I[j][i]);
        }
        fprintf(pfile, "\n");        
    }  

    //imprimindo no Log a matriz U;
    fprintf(pfile, "\nMatriz Tensão:\n");
    for (int i = 0; i < 3; i++)
    {
        fprintf(pfile, "\t\t\t\t%d", U[i]);
        fprintf(pfile, "\n");
    }
    
    //imprime determinante no log;
    fprintf(pfile, "\nDeterminante: %d", determinante3());

    //imprimindo Matriz inversa no Log;
    fprintf(pfile, "\n\nMatriz Inversa:\n");
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            fprintf(pfile, "\t\t\t\t%Lf ", d[j][i]);
        }
        fprintf(pfile, "\n");     
    } 
    
    fprintf(pfile, "\n");
    fprintf(pfile,"Corrente %d = %Lf\n", 1, a[0][0]);
    fprintf(pfile,"Corrente %d = %Lf\n", 2, a[0][1]);
    fprintf(pfile,"Corrente %d = %Lf\n\n", 3, a[0][2]);

    fprintf(pfile, "----------------------------------------");
    fclose(pfile);    

}

//Se a expressão apresentar erros pede que a insira novamente.
int validaEquacao(char x[]){

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

    //verifica se a quantidade de ponto achado é igual a 3;
    
    if (ponto != 3)
    {
        printf("Equação invalida, Lembrese do '.'!");
        return 0;
    }

    //verifica se a quantidade de sinal achado é igual a 4;
    if (sinal > 4)
    {
         printf("Equação invalida, não esqueça dos sinais(+-) antes de cada numero!\n");
        return 0;
    }    
    
    //verifica se o codigo é muito pequeno ou muito grande;
    if (tamanho <= 16 || tamanho >=  28)
    {
        printf("Equação invalida, divergencia no tamanho!\n");
        return 0;
    }
    return 1;

}

//calcula a determinante;
int determinante3()
{  
   //multiplicacao da diagonal principal;
    dp=(I[0][0]*I[1][1]*I[2][2]) + (I[0][1]*I[1][2]*I[2][0]) + (I[0][2]*I[1][0]*I[2][1]);
    //multiplica diagonal secundaria;
    ds=(I[0][2]*I[1][1]*I[2][0]) + (I[0][0]*I[1][2]*I[2][1]) + (I[0][1]*I[1][0]*I[2][2]);
    //determinante;
    dr=dp-ds;
    return dr;
} 

//inverte a matriz;
void inv3()
{
    float temp[3][3], det = determinante3();

    //calculo da matriz adjacente e inversa
    //divide a adjacente pelo determinante resultando na inversa
    d[0][0] = ((I[1][1] * I[2][2]) - (I[1][2] * I[2][1]))/det;
    d[0][1] = ((I[2][1] * I[0][2]) - (I[2][2] * I[0][1]))/det;
    d[0][2] = ((I[0][1] * I[1][2]) - (I[0][2] * I[1][1]))/det;

    d[1][0] = ((I[1][2] * I[2][0]) - (I[1][0] * I[2][2]))/det;
    d[1][1] = ((I[2][2] * I[0][0]) - (I[2][0] * I[0][2]))/det;
    d[1][2] = ((I[0][2] * I[1][0]) - (I[0][0] * I[1][2]))/det;

    d[2][0] = ((I[1][0] * I[2][1]) - (I[1][1] * I[2][0]))/det;
    d[2][1] = ((I[2][0] * I[0][1]) - (I[2][1] * I[0][0]))/det;
    d[2][2] = ((I[0][0] * I[1][1]) - (I[0][1] * I[1][0]))/det; 
}

//captura os dados da string para variaveis;
void input3(char y[], int qual)
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
            char x[marcador+1];

            //define x com os valores apos '=';
            for (int j = 0; j < marcador; j++)
            {
                //printf("\n temp[%d] = %c\n", j, y[i+j]);
                x[j] = y[h+j];

            }

            //fecha a string;
            x[marcador] = '\0';

            //chama stoi3(x), para transformar em int[];
            U[qual] = stoi3(x);
        }
        
    }    

}

// Transforma de string para int "char x[], é um ponteiro";
int stoi3(char *x)
{
    
    //inicializa variaveis;
    int teste[strlen(x)], menos, z = 0;

    //verifica se o numero é negativo;
    if(x[0] == '-')
    {
        z = 1;//se for negativo z recebe 1;
    }

    //for pulando a primeira posição do vetor passando char x para int teste;
    for (int i = 1; i < strlen(x); i++)
    {
        teste[i] = x[i]-48;//faz a conversão de cada posição do vetor para int(faz se -48 por causa da tabela ascii);
        //printf("\n\t\tteste[%d] = %d\n", i, teste[i]);
    }
    if(strlen(x) == 2)//se x tiver 2, ou seja ser apenas 1 numero;
    {
        menos = concatena(0/*centena*/, 0/*dezena*/, teste[1]/*unidade*/);
    }
    
    else if (strlen(x) == 3)//se x tiver 3, ou seja ser 2 numero;
    {
        menos = concatena(0, teste[1], teste[2]);
    }
    
    else if (strlen(x) == 4)//se x tiver 4, ou seja ser 3 numero;
    {       
        menos = concatena(teste[1], teste[2], teste[3]);
    }
    
    if(z == 1)// verifica se z é igual a 1; sendo multiplica por -1, para inverter o sinal;
    {
        //printf("aqui o menos = %d, teste[0] = %d", menos, teste[0]);
        menos = menos * -1;
        return menos;//retorna o numero negativo;
    }return menos;//retorna o numero positivo;
    
}

//multiplica as matriz;
void result3()
{
    a[0][0] = (d[0][0] * U[0]) + (d[0][1] * U[1]) + (d[0][2] * U[2]);
    a[0][1] = (d[1][0] * U[0]) + (d[1][1] * U[1]) + (d[1][2] * U[2]);
    a[0][2] = (d[2][0] * U[0]) + (d[2][1] * U[1]) + (d[2][2] * U[2]);   

    printf(" Corrente %d = %Lf\n", 1, a[0][0]);
    printf("\t   Corrente %d = %Lf\n", 2, a[0][1]);
    printf("\t   Corrente %d = %Lf\n", 3, a[0][2]);
    puts("");
}