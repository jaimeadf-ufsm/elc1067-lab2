#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_CNH 21
#define TAMANHO_NOME 101
#define TAMANHO_TELEFONE 21

typedef struct cliente Cliente;

struct cliente
{
    char cnh[TAMANHO_CNH];
    char nome[TAMANHO_NOME];
    char telefone[TAMANHO_TELEFONE];

    Cliente *proximo;
};

Cliente *criar_cliente(Cliente **lista);
Cliente *buscar_cliente(Cliente *lista, char *cnh);

void imprimir_todos_clientes(Cliente *lista);

void imprimir_informacoes_do_cliente(Cliente *cliente);
void imprimir_resumo_do_cliente(Cliente *cliente);

#endif 