#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "match.h"

int main()
{
    int width, height;

    printf("Dimensoes:\n");

    printf("Digite o numero de linhas da matriz: ");
    scanf(" %d", &height);

    printf("Digite o numero de colunas da matriz: ");
    scanf(" %d", &width);

    Matrix matrix = create_matrix(width, height);

    printf("\nPreenchimento:\n");
    printf("Digite o texto para preencher a matriz: ");
    fill_matrix(&matrix);

    printf("\n\n");
    show_matrix(&matrix);

    while (true)
    {
        char *word;

        printf("\n\nQual palavra voce deseja buscar? ");
        scanf("%ms", &word);

        Matches matches = search_word(&matrix, word);

        show_matches(&matches, word);
        release_matches(&matches);

        free(word);
    }

    release_matrix(&matrix);
}