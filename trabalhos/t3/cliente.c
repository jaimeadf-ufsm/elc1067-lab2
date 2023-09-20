#include "cliente.h"

Cliente *criar_cliente(Cliente **lista)
{
    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));

    if (cliente == NULL)
    {
        return NULL;
    }

    cliente->proximo = *lista;
    *lista = cliente;

    return cliente;
}

Cliente *buscar_cliente(Cliente *lista, char *cnh)
{
    for (Cliente *cliente = lista; cliente != NULL; cliente = cliente->proximo)
    {
        if (strcmp(cliente->cnh, cnh) == 0)
        {
            return cliente;
        }
    }

    return NULL;
}
void imprimir_todos_clientes(Cliente *lista)
{
    for (Cliente *cliente = lista; cliente != NULL; cliente = cliente->proximo)
    {
        imprimir_informacoes_do_cliente(cliente);
    }
}

void imprimir_resumo_do_cliente(Cliente *cliente)
{
    printf("%s (CNH: %s)\n", cliente->nome, cliente->cnh);
}

void imprimir_informacoes_do_cliente(Cliente *cliente)
{
    printf("• CNH:             %s\n", cliente->cnh);
    printf("  Nome:            %s\n", cliente->nome);
    printf("  Telefone:        %s\n", cliente->telefone);
    printf("\n");
}