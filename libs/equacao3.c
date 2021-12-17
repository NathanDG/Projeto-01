#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

//declara as funções
void input(char y[], int qual);
int stoi(char x[]);
int concatena(int c, int d, int u);
int determinante();
void inv();
void result();

//I[equacao1,2,3,][I1,2,3], u[equacao];
static int pos[2], posn = 0, I[3][3], U[3], h = 0;

//variaveis para multiplicação e inversão de matrizes;
static long double x[3][3], a[3][1], d[3][3];

int equacao3(){
    
    char equacao[50] = {"-67.i1-51.i2-58.i3=84"};
    //inserindo as equacoes;
    printf("Seguir o modelo:  +20.i1+304.i2-1.i3=+9\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Informe a equacao - %d: ", i+1);
        fgets(equacao, sizeof(equacao)-2, stdin);
        input(equacao, i);
    }

    //calcula o determinante
    determinante();

    //inverte a matriz
    inv();
    
    //mostra o resultado;
    printf("\nResultado:");
    result(); 
    return 1;
}

//calcula a determinante;
int determinante()
{ 
    int dp=0, ds=0, dr=0, det=0;
    //multiplicacao da diagonal principal
    dp=(I[0][0]*I[1][1]*I[2][2]) + (I[0][1]*I[1][2]*I[2][0]) + (I[0][2]*I[1][0]*I[2][1]);
    //multiplica diagonal secund�ria
    ds=(I[0][2]*I[1][1]*I[2][0]) + (I[0][0]*I[1][2]*I[2][1]) + (I[0][1]*I[1][0]*I[2][2]);
    //determinante
    dr=dp-ds;
    return dr;
} 

//inverte a matriz
void inv()
{
    float temp[3][3], det = determinante();
    //calculo da matriz inversa
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
void input(char y[], int qual)
{
    //contador que define I:1,2,3 na matriz;
    int contador = 0;

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
                }
            }

            posn = pos[0] - pos[1];//define a posição incial do que achou;

            //printf("\npos[0] = %d;\n pos[1] = %d\n posf = %d\n x = %d\n", pos[0], pos[1], posn, strlen(y)-posn);

            //inicializa variavel temporaria que armazena char que será transformado em int;
            char temp[pos[1]+1];

            //define com as posições que achou;
            for (int k = posn; k < posn + pos[1]; k++)
            {
                temp[k-posn] = y[k];
                //printf("\n\ttemp[%d] = %c", k-posn, y[k]);
            }

            temp[pos[1]] = '\0';
                 
            //transforma de sting para int;
            I[qual][contador-1] = stoi(temp);

            //printf("\nqual = %d, contador = %d", qual, contador);
            //printf("\n I[%d][%d] = %d\n", qual, contador-1, stoi(temp));
        }

        //procura por '=';
        if (y[i] == '=')
        { 
            h = i+1; 
            
            //marcador guardara o tamanho do char que chegou
            int marcador = (strlen(y)-h)-1;

            //inicializa variavel que armazena char que será transformado em int;
            char x[marcador+1];
            
            //printa quantas posiçoes foram criadas no vetor x;
            //printf("\nX tem[%d]\n", marcador);

            //define x;
            for (int j = 0; j < marcador; j++)
            {
                //printf("\n temp[%d] = %c\n", j, y[i+j]);
                x[j] = y[h+j];

            }

            x[marcador] = '\0';

            //chama stoi(x), para transformar em int[];
            U[qual] = stoi(x);
        }
        
    }    

}

// Transforma de string para int "char x[], é um ponteiro";
int stoi(char *x)
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

//concatena int de 3 digitos;
int concatena(int c, int d, int u){

    int r;
    r = c * 100; //centena;
    r = r + (d*10);//dezena;
    r = r + u;//unidade;
    return r;
}

//multiplica as matriz;
void result()
{
    a[0][0] = (d[0][0] * U[0]) + (d[0][1] * U[1]) + (d[0][2] * U[2]);
    a[0][1] = (d[1][0] * U[0]) + (d[1][1] * U[1]) + (d[1][2] * U[2]);
    a[0][2] = (d[2][0] * U[0]) + (d[2][1] * U[1]) + (d[2][2] * U[2]);   

    printf(" Corrente %d = %Lf\n", 1, a[0][0]);
    printf("\t   Corrente %d = %Lf\n", 2, a[0][1]);
    printf("\t   Corrente %d = %Lf\n", 3, a[0][2]);
    puts("");
}