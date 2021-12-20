#include <stdio.h>
#include <stdlib.h>
#include "libs/biblioteca.h"

int main() {
   
    int c1,c2,x = 0;
    
    while(x == 0){

        system("clear");
        printf("\n1-Resolver equações circuito elétrico?\n2-Obter o valor de saída da expressão booleana?\n3-sair\n");
        printf("\nQual opcão deseja fazer? \n");

        scanf("%d", &c1);    
        
        switch(c1){
        
        case 1:
            system("clear");
            printf("Inserir:  1-equacões duas malhas?  \n          2-equações três malhas?\n          3-Sair\n");
            printf("\nEm qual formato ?");
            int cl = 1;

            while(cl == 1 )
            {
                scanf("%d",&c2);
                if (c2 == 1)
                {
                    equacao2();
                    printf("Digite enter para retornar ");
                    getchar();
                    cl = 0;
                }
                if (c2 == 2)
                {
                    equacao3();
                    printf("Digite enter para retornar ");
                    getchar();
                    cl = 0;
                }
                if (c2 == 3)
                {
                    cl = 0;
                }                
                
                
                                
            }break;

        case 2:
        printf("digite a espressão:");
        scanf("%d",&c2);
        break;    
        
        case 3:
        printf("tchauzinho!\n");
        x = 1;
        break;

        default:
                printf("Digite um ou dois !\n");
                break;
        }
        
    }
    
    
}