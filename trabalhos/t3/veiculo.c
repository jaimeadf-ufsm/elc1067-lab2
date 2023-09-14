#include "veiculo.h"

void imprimir_veiculo_completo(Veiculo *veiculo)
{
    printf("- Placa: %s\n", veiculo->placa);
    printf("- Marca: %s\n", veiculo->marca);
    printf("- Modelo: %s\n", veiculo->modelo);
    printf("- Ano de fabricacao: %d\n", veiculo->ano_de_fabricacao);
    printf("- Quilometragem: %dkm\n", veiculo->quilometragem);
    printf("- Diaria: R$%.2lf\n", veiculo->diaria);
    printf("- Disponivel: %s\n", veiculo->disponivel ? "Sim" : "Nao");
}

void imprimir_veiculo_resumido(Veiculo *veiculo)
{
    printf(
        "%s %s %d (Placa: %s)\n",
        veiculo->marca,
        veiculo->modelo,
        veiculo->ano_de_fabricacao,
        veiculo->placa
    );
}

ListaVeiculo *inserir_veiculo(ListaVeiculo *lista, Veiculo *veiculo)
{
    ListaVeiculo *no = (ListaVeiculo *)malloc(sizeof(ListaVeiculo));
    no->veiculo = *veiculo;
    no->proximo = lista;

    return no;
}

Veiculo *buscar_veiculo(ListaVeiculo *lista, char *placa)
{
    for (ListaVeiculo *no = lista; no != NULL; no = no->proximo)
    {
        if (strcmp(no->veiculo.placa, placa) == 0)
        {
            return &no->veiculo;
        }
    }

    return NULL;
}

void imprimir_veiculos(ListaVeiculo *lista)
{
    int numero = 1;

    for (ListaVeiculo *no = lista; no != NULL; no = no->proximo)
    {
        printf("\nVeiculo %d\n", numero);        
        imprimir_veiculo_completo(&no->veiculo);

        numero++;        
    }
}

void imprimir_veiculos_disponiveis(ListaVeiculo *lista)
{
    int numero = 1;


    for (ListaVeiculo *no = lista; no != NULL; no = no->proximo)
    {
        if (no->veiculo.disponivel)
        {
            printf("%d. ", numero);        
            imprimir_veiculo_resumido(&no->veiculo);

            numero++;        
        }
    }
}

void obter_veiculos_mais_rodados(ListaVeiculo *lista, Veiculo **veiculos, int n)
{
    for (int i = 0; i < n; i++)
    {
        veiculos[i] = NULL;
    }

    for (ListaVeiculo *no = lista; no != NULL; no = no->proximo)
    {
        for (int i = 0; i < n; i++)
        {
            if (veiculos[i] == NULL || no->veiculo.quilometragem > veiculos[i]->quilometragem)
            {
                for (int j = n - 1; j > i; j--)
                {
                    veiculos[j] = veiculos[j - 1];
                }

                veiculos[i] = &no->veiculo;

                break;
            }
        }
    }
}