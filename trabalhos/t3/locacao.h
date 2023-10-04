#ifndef LOCACAO_H
#define LOCACAO_H

#include "veiculo.h"
#include "cliente.h"
#include "data.h"

typedef struct locacao Locacao;

struct locacao
{
    Veiculo *veiculo;
    Cliente *cliente;

    Data *data_de_retirada;
    Data *data_de_devolucao;
    
    double total;

    bool ativa;

    Locacao *proximo;
};

Locacao *alugar_veiculo(Locacao **lista, Veiculo *veiculo, Cliente *cliente, Data *data);
void devolver_veiculo(Locacao *locacao, Data *data, int quilometragem);

Locacao *buscar_locacao_em_andamento(Locacao *lista, char *placa);

bool existe_locacao_encerrada_em_data(Locacao *lista, char *placa, Data *inicio, Data *fim);

double contabilizar_faturamento(Locacao *lista, int mes, int ano);

void imprimir_todas_locacoes(Locacao *lista);
void imprimir_locacoes_em_data(Locacao *lista, Data *data);
void imprimir_locacoes_de_cliente(Locacao *lista, char *cnh);

void imprimir_locacao(Locacao *locacao);

#endif