#include <stdio.h>

#define NUM 50

struct usuario
{
    char sexo;
    int idade;
    int qtdade;
};

typedef struct usuario Usuario;

void leVetor(int tamanho, Usuario* vet)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("\nUsuario %d:\n", i + 1);

        printf("Digite o sexo ('m' ou 'f'): ");
        scanf(" %c", &vet[i].sexo);

        printf("Digite a idade: ");
        scanf("%d", &vet[i].idade);

        printf("Digite a quantidade de livros lidos: ");
        scanf("%d", &vet[i].qtdade);
    }
}

int calculaQtidadeLivros(int tamanho, Usuario* vet)
{
    int total = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (vet[i].idade < 10)
        {
            total += vet[i].qtdade;
        }
    }

    return total;
}

int calculaQtidadeMulheres(int tamanho, Usuario* vet)
{
    int qtd = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (vet[i].sexo == 'f' && vet[i].qtdade >= 5)
        {
            qtd++;
        }
    }

    return qtd;
}

int main()
{
    Usuario usuarios[NUM];

    leVetor(NUM, usuarios);
    int totalLivrosLidosPorCriancas = calculaQtidadeLivros(NUM, usuarios);
    int quantidadeDeLeitoras = calculaQtidadeMulheres(NUM, usuarios);

    printf("\n");
    printf("Total de livros lidos por criancas menores de 10 anos: %d\n", totalLivrosLidosPorCriancas);
    printf("Quantidade de mulheres que leram 5 livros ou mais: %d\n", quantidadeDeLeitoras);

    return 0;
}