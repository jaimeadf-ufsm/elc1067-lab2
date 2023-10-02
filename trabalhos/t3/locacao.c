#include "locacao.h"

Locacao *alugar_veiculo(Locacao **lista, Veiculo *veiculo, Cliente *cliente, Data *data)
{
    Locacao *locacao = (Locacao *)malloc(sizeof(Locacao));

    if (locacao == NULL)
    {
        return NULL;
    }

    veiculo->disponivel = false;

    locacao->veiculo = veiculo;
    locacao->cliente = cliente;
    locacao->data_de_retirada = data;
    locacao->data_de_devolucao = NULL;
    locacao->total = 0.0;
    locacao->ativa = true;
    locacao->proximo = *lista;

    *lista = locacao;

    return locacao;
}

void devolver_veiculo(Locacao *locacao, Data *data, int quilometragem)
{
    int duracao = diferenca_em_dias(locacao->data_de_retirada, data);

    if (duracao <= 0)
    {
        duracao = 1;
    }

    locacao->data_de_devolucao = data;
    locacao->total = duracao * locacao->veiculo->diaria;
    locacao->ativa = false;

    locacao->veiculo->quilometragem = quilometragem;
    locacao->veiculo->disponivel = true;
}

Locacao *buscar_locacao_em_andamento(Locacao *lista, char *placa)
{
    for (Locacao *locacao = lista; locacao != NULL; locacao = locacao->proximo)
    {
        if (strcmp(locacao->veiculo->placa, placa) == 0 && locacao->ativa)
        {
            return locacao;
        }
    }

    return NULL;
}

bool existe_locacao_em_data(Locacao *lista, char *placa, Data *inicio, Data *fim)
{
    for (Locacao *locacao = lista; locacao != NULL; locacao = locacao->proximo)
    {
        if (locacao->ativa)
        {
            continue;
        }

        if (strcmp(locacao->veiculo->placa, placa) != 0)
        {
            continue;
        }

        if (existe_sobreposicao_entre_datas(locacao->data_de_retirada, locacao->data_de_devolucao, inicio, fim))
        {
            return true;
        }
    }

    return false;
}

double contabilizar_faturamento(Locacao *lista, int mes, int ano)
{
    double faturamento = 0.0;

    for (Locacao *locacao = lista; locacao != NULL; locacao = locacao->proximo)
    {
        if (locacao->ativa)
        {
            continue;
        }

        if (locacao->data_de_retirada->mes != mes || locacao->data_de_retirada->ano != ano)
        {
            continue;
        }

        faturamento += locacao->total;
    }

    return faturamento;
}

void imprimir_todas_locacoes(Locacao *lista)
{
    for (Locacao *locacao = lista; locacao != NULL; locacao = locacao->proximo)
    {
        imprimir_locacao(locacao);
    }
}


void imprimir_locacoes_em_andamento(Locacao *lista)
{
    for (Locacao *locacao = lista; locacao != NULL; locacao = locacao->proximo)
    {
        if (locacao->ativa)
        {
            imprimir_locacao(locacao);
        }
    }
}

void imprimir_locacoes_de_cliente(Locacao *lista, char *cnh)
{
    for (Locacao *locacao = lista; locacao != NULL; locacao = locacao->proximo)
    {
        if (strcmp(locacao->cliente->cnh, cnh) == 0)
        {
            imprimir_locacao(locacao);
        }
    }
}

void imprimir_locacao(Locacao *locacao)
{
    printf("• Veiculo:         ");
    imprimir_resumo_do_veiculo(locacao->veiculo);
    printf("  Cliente:         ");
    imprimir_resumo_do_cliente(locacao->cliente);
    printf("  Retirada:        ");
    imprimir_data(locacao->data_de_retirada);

    if (!locacao->ativa)
    {
        printf("  Devolução:       ");
        imprimir_data(locacao->data_de_devolucao);
        printf("  Total:           R$ %.2lf\n", locacao->total);
    }

    printf("  Situação:        %s\n", locacao->ativa ? "Em andamento" : "Encerrada");
    printf("\n");
}