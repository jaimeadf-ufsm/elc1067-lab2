#include "cliente.h"

void imprimir_cliente_completo(Cliente *cliente)
{
    printf("- CNH: %s\n", cliente->cnh);
    printf("- Nome: %s\n", cliente->nome);
    printf("- Telefone: %s\n", cliente->telefone);
}

void imprimir_cliente_resumido(Cliente *cliente)
{
    printf("%s (CNH: %s)\n", cliente->nome, cliente->cnh);
}

ListaCliente *inserir_cliente(ListaCliente *lista, Cliente *cliente)
{
    ListaCliente *no = (ListaCliente *)malloc(sizeof(ListaCliente));
    no->cliente = *cliente;
    no->proximo = lista;

    return no;
}

Cliente *buscar_cliente(ListaCliente *lista, char *cnh)
{
    for (ListaCliente *no = lista; no != NULL; no = no->proximo)
    {
        if (strcmp(no->cliente.cnh, cnh) == 0)
        {
            return &no->cliente;
        }
    }

    return NULL;
}

void imprimir_clientes(ListaCliente *lista)
{
    int numero = 1;

    for (ListaCliente *no = lista; no != NULL; no = no->proximo)
    {
        printf("\nCliente %d\n", numero);
        imprimir_cliente_completo(&no->cliente);

        numero++;
    }
}