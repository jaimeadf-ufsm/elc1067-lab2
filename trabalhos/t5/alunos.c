#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alunos.h"

Aluno *criar_alunos() {
    return NULL;
}

Aluno *adicionar_aluno(Aluno *lista, int matricula, char *nome, int ano) {
    Aluno *novo = (Aluno *)malloc(sizeof(Aluno));

    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    novo->ano_de_ingresso = ano;

    Aluno *anterior = NULL;
    Aluno *atual = lista;

    while (atual != NULL && atual->matricula <= novo->matricula) {
        anterior = atual;
        atual = atual->proximo;
    }

    novo->proximo = atual;

    if (anterior == NULL) {
        return novo;
    }

    anterior->proximo = novo;

    return lista;
}

Aluno *remover_aluno(Aluno *lista, int matricula) {
    Aluno *anterior = NULL;
    Aluno *atual = lista;

    while (atual != NULL && atual->matricula != matricula) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return lista;
    }

    Aluno *prox = atual->proximo;
    free(atual);

    if (anterior == NULL) {
        return prox;
    }

    anterior->proximo = prox;

    return lista;
}

void liberar_alunos(Aluno *alunos) {
    Aluno *atual = alunos;

    while (atual != NULL) {
        Aluno *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

Aluno *buscar_aluno(Aluno *lista, int matricula) {
    for (Aluno *aluno = lista; aluno != NULL; aluno = aluno->proximo) {
        if (aluno->matricula == matricula) {
            return aluno;
        }
    }

    return NULL;
}


void imprimir_aluno(Aluno *aluno) {
    printf("- %d: %s (%d)\n", aluno->matricula, aluno->nome, aluno->ano_de_ingresso);
}

void imprimir_alunos(Aluno *lista) {
    for (Aluno *aluno = lista; aluno != NULL; aluno = aluno->proximo) {
        printf(aluno->proximo == NULL ? "`" : "|");
        imprimir_aluno(aluno);
    }
}
