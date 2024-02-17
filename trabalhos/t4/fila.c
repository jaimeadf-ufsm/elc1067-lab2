#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila *criar_fila(void){
    //retorna o ponteiro para a struct fila criada
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->ini = NULL;
    fila->fim = NULL;
    return fila;
}

void desalocar_fila(Fila *fila){
    Grupo *p = fila->ini;
    Grupo *ant = NULL;
    while(p != NULL){
        ant = p;
        p = p->prox;
        free(ant);
    }
    free(fila);
}

int entrar_na_fila(Fila *fila, int pessoas){
    //recebe a fila e o numero de pessoas que vao entrar na fila
    Grupo *n = (Grupo*)malloc(sizeof(Grupo));
    n->pessoas = pessoas;
    n->prox = NULL;

    if(fila_vazia(fila)) {
        n->senha = 1;
        fila->ini = n;
        fila->fim = n;
    } else {
        n->senha = fila->fim->senha+1;
        fila->fim->prox = n;
        fila->fim = n;
    }

    return n->senha;
}

int retirar_pessoas_da_fila(Fila *fila, int maximo){
    //recebe a fila
    //retorna o numero de pessoas chamadas
    
    if(fila_vazia(fila)){
        return 0; 
    }

    if (fila->ini->pessoas > maximo) {
        fila->ini->pessoas -= maximo;
        return maximo;
    }

    int pessoas = fila->ini->pessoas;
    sair_da_fila(fila, fila->ini->senha);

    return pessoas;
}

bool sair_da_fila(Fila *fila, int senha){
    //recebe a fila e a senha do grupo que desistiu de esperar
    Grupo *p = fila->ini;
    Grupo *ant = NULL;
    
    while(p != NULL && p->senha != senha){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        return false;
    }

    if(ant == NULL) {
        fila->ini = p->prox;

        if (fila->ini == NULL) {
            fila->fim = NULL;
        }
    } else {
        ant->prox = p->prox;

        if(ant->prox == NULL){
            fila->fim = ant;
        }
    }

    free(p);
    
    return true;
}

bool fila_vazia(Fila *fila){
    if(fila->ini == NULL && fila->fim == NULL) return true;
    return false;
}

void imprimir_fila(Fila *fila) {
    if (fila_vazia(fila)) {
        printf("• A fila de espera está vazia.\n");
        return;
    }

    int numero_de_grupos = 0;
    int numero_de_pessoas = 0;

    for (Grupo *grupo = fila->ini; grupo != NULL; grupo = grupo->prox) {
        printf("• Grupo %2d: %3d pessoa(s)\n", grupo->senha, grupo->pessoas);

        numero_de_grupos++;
        numero_de_pessoas += grupo->pessoas;
    }

    printf("\n");
    printf("• %d grupo(s) com um total de %d pessoa(s) aguarda(m) na fila de espera.\n", numero_de_grupos, numero_de_pessoas);
}
