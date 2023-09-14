#include "locacao.h"

void imprimir_locacao(Locacao *locacao)
{
    printf("- Veiculo: ");
    imprimir_veiculo_resumido(locacao->veiculo);
    printf("- Cliente: ");
    imprimir_cliente_resumido(locacao->cliente);
    printf("- Data de retirada: %02d/%02d/%04d\n", locacao->data_retirada.dia, locacao->data_retirada.mes, locacao->data_retirada.ano);

    if (locacao->ativa)
    {
        printf("- Data de devolucao: (locacao em andamento)\n");
    }
    else
    {
        printf("- Data de devolucao: %02d/%02d/%04d\n", locacao->data_devolucao.dia, locacao->data_devolucao.mes, locacao->data_devolucao.ano);
    }
}

Locacao *buscar_locacao_ativa(ListaLocacao *lista, char *placa)
{
    for (ListaLocacao *no = lista; no != NULL; no = no->proximo)
    {        
        if (no->locacao.ativa && strcmp(no->locacao.veiculo->placa, placa) == 0)
        {
            return &no->locacao; 
        }
    }

    return NULL;
}

void imprimir_locacoes_ativas(ListaLocacao *lista)
{
    int numero = 1;

    for (ListaLocacao *no = lista; no != NULL; no = no->proximo)
    {
        if (no->locacao.ativa)
        {
            printf("\nLocacao %d\n", numero);
            imprimir_locacao(&no->locacao);

            numero++;
        }
    }
}

void imprimir_locacoes_de_cliente(ListaLocacao *lista, char *cnh)
{
    int numero = 1;

    for (ListaLocacao *no = lista; no != NULL; no = no->proximo)
    {
        if (strcmp(no->locacao.cliente->cnh, cnh) == 0)
        {
            printf("\nLocacao %d\n", numero);
            imprimir_locacao(&no->locacao);

            numero++;
        }
    }
}

ListaLocacao *alugar_veiculo(ListaLocacao *lista, Veiculo *veiculo, Cliente *cliente, Data data)
{
    ListaLocacao *no = (ListaLocacao *)malloc(sizeof(ListaLocacao));
    no->locacao.veiculo = veiculo;
    no->locacao.cliente = cliente;
    no->locacao.data_retirada = data;
    no->locacao.data_devolucao = (Data){0, 0, 0};
    no->locacao.ativa = true;
    no->proximo = lista;

    no->locacao.veiculo->disponivel = false;

    return no;
}

void devolver_veiculo(Locacao *locacao, Data data, int quilometragem)
{
    locacao->veiculo->disponivel = true;
    locacao->veiculo->quilometragem = quilometragem;
    locacao->data_devolucao = data;
    locacao->ativa = false;
}

double calcular_faturamento_de_locacoes(ListaLocacao *lista, int mes, int ano)
{
    double faturamento = 0.0;

    for (ListaLocacao *no = lista; no != NULL; no = no->proximo)
    {
        if (no->locacao.data_devolucao.ano == ano && no->locacao.data_devolucao.mes == mes)
        {
            int dias = calcular_diferenca_de_dias(no->locacao.data_retirada, no->locacao.data_devolucao);
            faturamento += no->locacao.veiculo->diaria * dias; 
        }
    }

    return faturamento;
}