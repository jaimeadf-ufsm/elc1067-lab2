#ifndef _CURSOS_H_
#define _CURSOS_H_

#include <stdbool.h>
#include "alunos.h"

#define TAMANHO_NOME_CURSO 101
#define TAMANHO_CENTRO_CURSO 101

typedef struct curso Curso;

struct curso {
    int codigo;

    char nome[TAMANHO_NOME_CURSO];
    char centro[TAMANHO_CENTRO_CURSO];

    Aluno *alunos;

    struct curso *esquerda;
    struct curso *direita;
};

Curso *criar_cursos();

bool cursos_vazio(Curso *arvore);

Curso *adicionar_curso(Curso *arvore, int codigo, char *nome, char *centro);
Curso *remover_curso(Curso *arvore, int codigo);

Curso *buscar_curso(Curso *arvore, int codigo);

void matricular_aluno(Curso *curso, int matricula, char *nome, int ano);
void desmatricular_aluno(Curso *curso, int matricula);

Aluno *buscar_matricula(Curso *curso, int matricula);

void imprimir_curso(Curso *curso);
void imprimir_cursos(Curso *arvore);

void imprimir_curso_com_alunos(Curso *curso);
void imprimir_cursos_com_alunos(Curso *arvore);

#endif