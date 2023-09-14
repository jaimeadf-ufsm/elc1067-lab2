#ifndef LOCADORA_H
#define LOCADORA_H

#include "veiculo.h"
#include "cliente.h"
#include "locacao.h"

typedef struct locadora Locadora;

struct locadora
{
    ListaVeiculo *veiculos;
    ListaCliente *clientes;
    ListaLocacao *locacoes;
};

#endif