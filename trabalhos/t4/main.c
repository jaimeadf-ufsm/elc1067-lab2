#include "menu.h"

int main() {
    int linhas, colunas;
    
    printf("Qual o número de linhas e de colunas do restaurante? ");
    scanf("%d %d", &linhas, &colunas);

    printf("\n");

    Restaurante *restaurante = criar_restaurante(linhas, colunas);
    menu(restaurante);
    desalocar_restaurante(restaurante);

    return 0;
}
