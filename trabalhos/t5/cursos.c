#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cursos.h"

Curso *criar_cursos() {
    return NULL;
}

bool cursos_vazio(Curso *arvore) {
    return arvore == NULL;
}

Curso *adicionar_curso(Curso *arvore, int codigo, char *nome, char *centro) {
    if (cursos_vazio(arvore)) {
        Curso *curso = (Curso *)malloc(sizeof(Curso));

        curso->codigo = codigo;
        strcpy(curso->nome, nome);
        strcpy(curso->centro, centro);

        curso->alunos = NULL;

        curso->esquerda = NULL;
        curso->direita = NULL;

        return curso;
    }

    if (codigo < arvore->codigo) {
        arvore->esquerda = adicionar_curso(arvore->esquerda, codigo, nome, centro);
    } else {
        arvore->direita = adicionar_curso(arvore->direita, codigo, nome, centro);
    }

    return arvore;
}

Curso *remover_raiz(Curso *arvore) {
    Curso *esquerda = arvore->esquerda;
    Curso *direita = arvore->direita;

    liberar_alunos(arvore->alunos);

    if (esquerda == NULL) {
        free(arvore);
        return direita;
    }

    Curso *pai = arvore;
    Curso *atual = esquerda;

    while (!cursos_vazio(atual->direita)) {
        pai = atual;
        atual = atual->direita;
    }

    if (pai != arvore) {
        pai->direita = atual->esquerda;
        atual->esquerda = esquerda;
    }

    atual->direita = direita;

    free(arvore);

    return atual;
}

Curso *remover_curso(Curso *arvore, int codigo) {
    if (cursos_vazio(arvore)) {
        return NULL;
    }

    if (codigo == arvore->codigo) {
        return remover_raiz(arvore);
    }

    if (codigo < arvore->codigo) {
        arvore->esquerda = remover_curso(arvore->esquerda, codigo);
    } else {
        arvore->direita = remover_curso(arvore->direita, codigo);
    }   

    return arvore;
}

Curso *buscar_curso(Curso *arvore, int codigo) {
    if (cursos_vazio(arvore)) {
        return NULL;
    }

    if (codigo < arvore->codigo) {
        return buscar_curso(arvore->esquerda, codigo);
    }

    if (codigo > arvore->codigo) {
        return buscar_curso(arvore->direita, codigo);
    }

    return arvore;
}

void matricular_aluno(Curso *curso, int matricula, char *nome, int ano) {
    curso->alunos = adicionar_aluno(curso->alunos, matricula, nome, ano);
}

void desmatricular_aluno(Curso *curso, int matricula) {
    curso->alunos = remover_aluno(curso->alunos, matricula);
}

Aluno *buscar_matricula(Curso *curso, int matricula) {
    return buscar_aluno(curso->alunos, matricula);
}

void imprimir_curso(Curso *curso) {
    printf("• %d: %s (%s)\n", curso->codigo, curso->nome, curso->centro);
}

void imprimir_cursos(Curso *arvore) {
    if (cursos_vazio(arvore)) {
        return;
    }

    imprimir_cursos(arvore->esquerda);
    imprimir_curso(arvore);
    imprimir_cursos(arvore->direita);
}

void imprimir_curso_com_alunos(Curso *curso) {
    imprimir_curso(curso);
    imprimir_alunos(curso->alunos);
    printf("\n");
}

void imprimir_cursos_com_alunos(Curso *arvore) {
    if (cursos_vazio(arvore)) {
        return;
    }

    imprimir_cursos_com_alunos(arvore->esquerda);
    imprimir_curso_com_alunos(arvore);
    imprimir_cursos_com_alunos(arvore->direita);
}