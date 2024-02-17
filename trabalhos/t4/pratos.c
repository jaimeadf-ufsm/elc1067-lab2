#include "pratos.h"
#include <stdlib.h>

Prato *criar_pilha_de_pratos(void){
    return NULL;
}

void desalocar_pilha_de_pratos(Prato *pilha){
    Prato *ant = NULL;
    while(pilha != NULL){
        ant = pilha;
        pilha = pilha->prox;
        free(ant);
    }
}

Prato *empilhar_prato(Prato *pilha){
    Prato *p = (Prato*)malloc(sizeof(Prato));
    p->prox = pilha;
    return p;
}

Prato *desempilhar_prato(Prato *pilha){
    if(pilha == NULL) return NULL;
    Prato *p = pilha->prox;
    free(pilha);
    return p;
}

int contar_pratos(Prato *pilha){
    int i = 0;
    for(Prato *p = pilha; p != NULL; p = p->prox){
        i++;
    }
    return i;
}

Prato *empilhar_pratos(Prato *pilha, int n){
    for(int i = 0; i < n; i++){
        pilha = empilhar_prato(pilha);
    }
    return pilha;
}

Prato *desempilhar_pratos(Prato *pilha, int n){
    for(int i = 0; i < n; i++){
        pilha = desempilhar_prato(pilha);
    }
    return pilha;
}
