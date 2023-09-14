#include "menu.h"
#include "locadora.h"

int main()
{
    Locadora locadora;
    locadora.clientes = NULL;
    locadora.veiculos = NULL;
    locadora.locacoes = NULL;

    menu(&locadora);

    return 0;
}