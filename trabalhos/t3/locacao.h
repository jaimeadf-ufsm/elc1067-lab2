#ifndef LOCACAO_H
#define LOCACAO_H

#include "veiculo.h"
#include "cliente.h"
#include "data.h"

typedef struct locacao Locacao;
typedef struct lista_locacao ListaLocacao;

struct locacao
{
    Veiculo *veiculo;
    Cliente *cliente;

    Data data_retirada;
    Data data_devolucao;

    bool ativa;
};

struct lista_locacao
{
    Locacao locacao;
    ListaLocacao *proximo; 
};

void imprimir_locacao(Locacao *locacao);

Locacao *buscar_locacao_ativa(ListaLocacao *lista, char *placa);

void imprimir_locacoes_ativas(ListaLocacao *lista);
void imprimir_locacoes_de_cliente(ListaLocacao *lista, char *cnh);

ListaLocacao *alugar_veiculo(ListaLocacao *lista, Veiculo *veiculo, Cliente *cliente, Data data);
void devolver_veiculo(Locacao *locacao, Data data, int quilometragem);

double calcular_faturamento_de_locacoes(ListaLocacao *lista, int mes, int ano);

#endif