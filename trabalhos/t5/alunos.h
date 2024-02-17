#ifndef _ALUNOS_H_
#define _ALUNOS_H_

#define TAMANHO_NOME_ALUNO 101

typedef struct aluno Aluno;

struct aluno {
    int matricula;
    int ano_de_ingresso;
    char nome[TAMANHO_NOME_ALUNO];

    struct aluno *proximo;
};

Aluno *criar_alunos();

Aluno *adicionar_aluno(Aluno *lista, int matricula, char *nome, int ano);
Aluno *remover_aluno(Aluno *lista, int matricula);

Aluno *buscar_aluno(Aluno *lista, int matricula);

void liberar_alunos(Aluno *alunos);

void imprimir_aluno(Aluno *aluno);
void imprimir_alunos(Aluno *lista);

#endif