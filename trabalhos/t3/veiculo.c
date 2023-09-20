#include "veiculo.h"

Veiculo *criar_veiculo(Veiculo **lista)
{
    Veiculo *veiculo = (Veiculo *)malloc(sizeof(Veiculo));

    if (veiculo == NULL)
    {
        return NULL;
    }

    veiculo->proximo = *lista;
    *lista = veiculo;

    return veiculo;
}

Veiculo *buscar_veiculo(Veiculo *lista, char *placa)
{
    for (Veiculo *veiculo = lista; veiculo != NULL; veiculo = veiculo->proximo)
    {
        if (strcmp(veiculo->placa, placa) == 0)
        {
            return veiculo;
        }
    }

    return NULL;
}

void separar_veiculos_mais_rodados(Veiculo *lista, Veiculo *vetor[], int n)
{
    for (int i = 0; i < n; i++)
    {
        vetor[i] = NULL;
    }

    for (Veiculo *veiculo = lista; veiculo != NULL; veiculo = veiculo->proximo)
    {
        for (int i = 0; i < n; i++)
        {
            if (vetor[i] == NULL || veiculo->quilometragem > vetor[i]->quilometragem)
            {
                for (int j = n - 1; j > i; j--)
                {
                    vetor[j] = vetor[j - 1];
                }

                vetor[i] = veiculo;

                break;
            }
        }
    }
}

void imprimir_todos_veiculos(Veiculo *lista)
{
    for (Veiculo *veiculo = lista; veiculo != NULL; veiculo = veiculo->proximo)
    {
        imprimir_informacoes_do_veiculo(veiculo);
    }
}

void imprimir_veiculos_disponiveis(Veiculo *lista)
{
    for (Veiculo *veiculo = lista; veiculo != NULL; veiculo = veiculo->proximo)
    {
        if (veiculo->disponivel)
        {
            printf("• ");
            imprimir_resumo_do_veiculo(veiculo);
        }
    }
}

void imprimir_resumo_do_veiculo(Veiculo *veiculo)
{
    printf(
        "%s %s %d (Placa: %s)\n",
        veiculo->marca,
        veiculo->modelo,
        veiculo->ano,
        veiculo->placa
    );
}

void imprimir_informacoes_do_veiculo(Veiculo *veiculo)
{
    printf("• Placa:           %s\n", veiculo->placa);
    printf("  Marca:           %s\n", veiculo->marca);
    printf("  Modelo:          %s\n", veiculo->modelo);
    printf("  Ano:             %d\n", veiculo->ano);
    printf("  Quilometragem:   %d km\n", veiculo->quilometragem);
    printf("  Diária:          R$ %.2lf\n", veiculo->diaria);
    printf("  Disponibilidade: %s\n", veiculo->disponivel ? "Disponível" : "Indisponível");
    printf("\n");
}