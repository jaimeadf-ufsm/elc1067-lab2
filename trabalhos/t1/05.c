#include <stdio.h>

struct aluno
{
    float nota1;
    float nota2;
    int aulasAssistidas;
    float media;
    char status;
};

typedef struct aluno Aluno;

struct disciplina
{
    Aluno vet[5];
    int aulasMinistradas;
};

typedef struct disciplina Disciplina;

void ler_disciplina(Disciplina *disciplina)
{
    printf("Digite o numero de aulas ministradas da disciplina: ");
    scanf("%d", &disciplina->aulasMinistradas);

    for (int i = 0; i < 5; i++)
    {
        printf("\nAluno %d\n", i + 1);

        printf("Digite a nota 1: ");
        scanf("%f", &disciplina->vet[i].nota1);

        printf("Digite a nota 2: ");
        scanf("%f", &disciplina->vet[i].nota2);

        printf("Digite a quantidade de aulas assistidas: ");
        scanf("%d", &disciplina->vet[i].aulasAssistidas);
    }
}

void verificar_alunos(Disciplina *disciplina)
{
    for (int i = 0; i < 5; i++)
    {
        float presenca = (float)disciplina->vet[i].aulasAssistidas / disciplina->aulasMinistradas;

        disciplina->vet[i].media = (disciplina->vet[i].nota1 + disciplina->vet[i].nota2) / 2;
        disciplina->vet[i].status = disciplina->vet[i].media >= 6 && presenca >= 0.75 ? 'A' : 'B';
    }
}

void mostrar_resultados(Disciplina *disciplina)
{
    printf("\nResultados:\n");
    
    for (int i = 0; i < 5; i++)
    {
        printf("Aluno %d\n", i + 1);
        printf("Media: %.2f\n", disciplina->vet[i].media);
        printf("Status: %c\n\n", disciplina->vet[i].status);
    }
}

int main()
{
    Disciplina disciplina;

    ler_disciplina(&disciplina);
    verificar_alunos(&disciplina);
    mostrar_resultados(&disciplina);
}