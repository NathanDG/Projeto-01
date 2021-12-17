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