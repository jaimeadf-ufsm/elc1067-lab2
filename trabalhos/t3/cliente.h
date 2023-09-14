#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_CNH 20
#define TAMANHO_NOME 100
#define TAMANHO_TELEFONE 20

typedef struct cliente Cliente;
typedef struct lista_cliente ListaCliente;

struct cliente
{
    char cnh[TAMANHO_CNH + 1];
    char nome[TAMANHO_NOME + 1];
    char telefone[TAMANHO_TELEFONE + 1];
};

struct lista_cliente
{
    Cliente cliente;
    ListaCliente *proximo;
};

void imprimir_cliente_completo(Cliente *cliente);
void imprimir_cliente_resumido(Cliente *cliente);

ListaCliente *inserir_cliente(ListaCliente *lista, Cliente *cliente);
Cliente *buscar_cliente(ListaCliente *lista, char *cnh);
void imprimir_clientes(ListaCliente *lista);

#endif 