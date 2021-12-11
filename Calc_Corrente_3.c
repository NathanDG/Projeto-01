#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int resto[1][3], i[3][3], dp, ds, dr, det;
double x[3][3], a[3][1], d[3][3];

void result()
{
    a[0][0] = (d[0][0] * resto[1][0]) + (d[0][1] * resto[1][1]) + (d[0][2] * resto[1][2]);
    a[0][1] = (d[1][0] * resto[1][0]) + (d[1][1] * resto[1][1]) + (d[1][2] * resto[1][2]);
    a[0][2] = (d[2][0] * resto[1][0]) + (d[2][1] * resto[1][1]) + (d[2][2] * resto[1][2]);   

    printf(" Corrente %d = %lf\n", 1, a[0][0]);
    printf("\t   Corrente %d = %lf\n", 2, a[0][1]);
    printf("\t   Corrente %d = %lf\n", 2, a[0][2]);
    printf("");
}
 
void main()
{
    char string[100] = "2.i1 + 3.i2 + 1.i3 = 0";

    //inserindo as equacoes;
    printf("Seguir o modelo:  13.i1 + 05.i2 + 12.i3 = 05\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Informe a equacao - %d: ", i+1);
        fgets(string, sizeof(string)-2, stdin);
        recuperaEquacao(string, i);
    }

    //montando matrizes;
    //matriz A;
    printf("\n Matriz A");
    for (int x = 0; x < 3; x++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("\t%d", i[x][j]);
            printf("\tA[%d][%d]", x, j);
        }
        printf("");
    }
    printf("");

    //matriz B;
    printf("\nMatriz B");
    for (int x = 0; x < 3; x++)
    {
        printf("\t%d", resto[1][x]);
        printf("\tresto[1][%d]", x);
        printf("");
    } 
    //calcula o determinante
    determinante();
    
    //inverte a matriz
    inv();
    
    printf("");
    printf("Determinante: %d", determinante());
    printf("\n\n");

    //imprime a matriz na tela
    printf("Matriz Inversa");
    printf("");
    for(int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        printf("\t%.2lf", d[j][i]);
        printf("");
    }
    printf("");

    printf("\nResultado:");
    //chama a fun��o resultado
    result(); 
}

//calcula a determinante;
int determinante()
{  
   //multiplicacao da diagonal principal
    dp=(i[0][0]*i[1][1]*i[2][2]) + (i[0][1]*i[1][2]*i[2][0]) + (i[0][2]*i[1][0]*i[2][1]);
    //multiplica diagonal secund�ria
    ds=(i[0][2]*i[1][1]*i[2][0]) + (i[0][0]*i[1][2]*i[2][1]) + (i[0][1]*i[1][0]*i[2][2]);
    //determinante
    dr=dp-ds;
    return dr;
} 

//inverte a matriz
void inv()
{
    float temp[3][3], det = determinante();
    //calculo da matriz inversa
    d[0][0] = ((i[1][1] * i[2][2]) - (i[1][2] * i[2][1]))/det;
    d[0][1] = ((i[2][1] * i[0][2]) - (i[2][2] * i[0][1]))/det;
    d[0][2] = ((i[0][1] * i[1][2]) - (i[0][2] * i[1][1]))/det;

    d[1][0] = ((i[1][2] * i[2][0]) - (i[1][0] * i[2][2]))/det;
    d[1][1] = ((i[2][2] * i[0][0]) - (i[2][0] * i[0][2]))/det;
    d[1][2] = ((i[0][2] * i[1][0]) - (i[0][0] * i[1][2]))/det;

    d[2][0] = ((i[1][0] * i[2][1]) - (i[1][1] * i[2][0]))/det;
    d[2][1] = ((i[2][0] * i[0][1]) - (i[2][1] * i[0][0]))/det;
    d[2][2] = ((i[0][0] * i[1][1]) - (i[0][1] * i[1][0]))/det; 
}

//converte ascci em decimal de 0-9
int ascii(int x)
{      
    return (x - 48);
}

//concatena inteiros;
unsigned concatenate(unsigned x, unsigned y) 
{ 
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;     
}

//separa a string em int;
void recuperaEquacao(char x[100], int y)
{
    int t1, t2;

    t1 = x[0];
    t2 = x[1];
    i[y][0] = concatenate(ascii(t1), ascii(t2));

    t1 = x[8];
    t2 = x[9];
    i[y][1] = concatenate(ascii(t1), ascii(t2));
    
    t1 = x[16];
    t2 = x[17];
    i[y][2] = concatenate(ascii(t1), ascii(t2));

    t1 = x[24];
    t2 = x[25];
    resto[1][y] = concatenate(ascii(t1), ascii(t2));
}