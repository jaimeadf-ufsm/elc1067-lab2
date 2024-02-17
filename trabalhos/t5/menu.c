#include <stdio.h>
#include "menu.h"

void imprimir_menu() {
    printf("> Menu:\n");
    printf("  1. adicionar curso\n");
    printf("  2. remover curso\n");
    printf("  3. matricular aluno\n");
    printf("  4. desmatricular aluno\n");
    printf("\n");
    printf("  a. imprimir matriculados em curso\n");
    printf("  b. imprimir cursos\n");
    printf("  c. imprimir vínculos\n");
    printf("\n");
    printf("  h. ajuda\n");
    printf("  0. sair\n");
}

Curso *perguntar_curso(Universidade *universidade) {
    int codigo;

    printf("- Código: ");
    scanf("%d", &codigo);

    Curso *curso = buscar_curso(universidade->cursos, codigo);

    if (curso == NULL) {
        printf("! O curso com o código %d não foi encontrado.\n", codigo);
    }

    return curso;
}

void opcao_adicionar_curso(Universidade *universidade) {
    printf("# Adicionar Curso\n");

    int codigo;
    char nome[TAMANHO_NOME_CURSO];
    char centro[TAMANHO_CENTRO_CURSO];

    printf("- Código: ");
    scanf("%d", &codigo);

    printf("- Nome:   ");
    scanf(" %100[^\n]", nome);

    printf("- Centro: ");
    scanf(" %100[^\n]", centro);

    universidade->cursos = adicionar_curso(universidade->cursos, codigo, nome, centro);

    printf("! O curso %s foi oficialmente registrado.\n", nome);
}

void opcao_remover_curso(Universidade *universidade) {
    printf("# Remover Curso\n");

    Curso *curso = perguntar_curso(universidade);

    if (curso == NULL) {
        return;
    }

    printf("! O curso %s foi removido.\n", curso->nome);
    universidade->cursos = remover_curso(universidade->cursos, curso->codigo);
}

void opcao_matricular_aluno(Universidade *universidade) {
    printf("# Adicionar Aluno a Curso\n");

    Curso *curso = perguntar_curso(universidade);

    if (curso == NULL) {
        return;
    }

    int matricula;
    int ano_de_ingresso;
    char nome[TAMANHO_NOME_ALUNO];

    printf("- Matrícula: ");
    scanf("%d", &matricula);

    printf("- Nome:      ");
    scanf(" %100[^\n]", nome);

    printf("- Ano de Ingresso: ");
    scanf("%d", &ano_de_ingresso);

    matricular_aluno(curso, matricula, nome, ano_de_ingresso);
    printf("! O aluno %s foi matriculado no curso %s.\n", nome, curso->nome);
}

void opcao_desmatricular_aluno(Universidade *universidade) {
    printf("# Remover Aluno de Curso\n");

    Curso *curso = perguntar_curso(universidade);

    if (curso == NULL) {
        return;
    }

    int matricula;

    printf("- Matrícula: ");
    scanf("%d", &matricula);

    Aluno *aluno = buscar_aluno(curso->alunos, matricula);

    if (aluno == NULL) {
        printf("! O aluno com a matrícula %d não está matriculado no curso %s.\n", matricula, curso->nome);
        return;
    }

    printf("! O aluno %s foi desmatriculado do curso %s.\n", aluno->nome, curso->nome);
    desmatricular_aluno(curso, matricula);
}

void opcao_imprimir_matriculados_em_curso(Universidade *universidade) {
    printf("# Matriculados em Curso\n");

    Curso *curso = perguntar_curso(universidade);

    if (curso == NULL) {
        return;
    }

    imprimir_curso_com_alunos(curso);
}

void opcao_imprimir_cursos(Universidade *universidade) {
    printf("# Cursos\n");
    imprimir_cursos(universidade->cursos);
}

void opcao_imprimir_vinculos(Universidade *universidade) {
    printf("# Vínculos\n");
    imprimir_cursos_com_alunos(universidade->cursos);
}

void menu(Universidade *universidade) {
    char opcao;

    imprimir_menu();

    do {
        printf("\n$ O que você deseja fazer? ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                opcao_adicionar_curso(universidade);
                break;
            case '2':
                opcao_remover_curso(universidade);
                break;
            case '3':
                opcao_matricular_aluno(universidade);
                break;
            case '4':
                opcao_desmatricular_aluno(universidade);
                break;
            case 'a':
                opcao_imprimir_matriculados_em_curso(universidade);
                break;
            case 'b':
                opcao_imprimir_cursos(universidade);
                break;
            case 'c':
                opcao_imprimir_vinculos(universidade);
                break;
            case 'h':
                imprimir_menu();
                break;
            case '0':
                break;
            default:
                printf("! Opção inválida.\n");
                break;
        }
    } while (opcao != '0');
}