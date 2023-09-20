#ifndef LOCADORA_H
#define LOCADORA_H

#include "veiculo.h"
#include "cliente.h"
#include "locacao.h"

typedef struct locadora Locadora;

struct locadora
{
    Veiculo *veiculos;
    Cliente *clientes;
    Locacao *locacoes;
};

#endif