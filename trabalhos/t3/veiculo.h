#ifndef VEICULO_H
#define VEICULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO_PLACA 10
#define TAMANHO_MARCA 100
#define TAMANHO_MODELO 100

typedef struct veiculo Veiculo;
typedef struct lista_veiculo ListaVeiculo;

struct veiculo
{
    char placa[TAMANHO_MARCA + 1];

    char marca[TAMANHO_MARCA + 1];
    char modelo[TAMANHO_MODELO + 1];    
    int ano_de_fabricacao;

    int quilometragem;

    double diaria;
    bool disponivel;
};

struct lista_veiculo
{
    Veiculo veiculo;
    ListaVeiculo *proximo;
};

void imprimir_veiculo_completo(Veiculo *veiculo);
void imprimir_veiculo_resumido(Veiculo *veiculo);

ListaVeiculo *inserir_veiculo(ListaVeiculo *lista, Veiculo *veiculo);
Veiculo *buscar_veiculo(ListaVeiculo *lista, char *placa);

void imprimir_veiculos(ListaVeiculo *lista);
void imprimir_veiculos_disponiveis(ListaVeiculo *lista);

void obter_veiculos_mais_rodados(ListaVeiculo *lista, Veiculo **veiculos, int n);

#endif