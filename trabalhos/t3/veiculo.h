#ifndef VEICULO_H
#define VEICULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO_PLACA 21
#define TAMANHO_MARCA 101
#define TAMANHO_MODELO 101

typedef struct veiculo Veiculo;

struct veiculo
{
    char placa[TAMANHO_PLACA];

    char marca[TAMANHO_MARCA];
    char modelo[TAMANHO_MODELO];    
    int ano;

    int quilometragem;

    double diaria;
    bool disponivel;

    Veiculo *proximo;
};

Veiculo *criar_veiculo(Veiculo **lista);
Veiculo *buscar_veiculo(Veiculo *lista, char *placa);

void separar_veiculos_mais_rodados(Veiculo *lista, Veiculo *vetor[], int n);

void imprimir_todos_veiculos(Veiculo *lista);
void imprimir_veiculos_disponiveis(Veiculo *lista);

void imprimir_resumo_do_veiculo(Veiculo *veiculo);
void imprimir_informacoes_do_veiculo(Veiculo *veiculo);

#endif