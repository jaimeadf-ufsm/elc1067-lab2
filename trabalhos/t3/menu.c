#include "menu.h"

#define LARGURA_CABECALHO 80
#define TAMANHO_VEICULOS_MAIS_RODADOS 3

void repetir_texto(char *texto, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", texto);
    }
}

void imprimir_cabecalho(char *titulo)
{
    printf("» %s ", titulo);
    repetir_texto("«", LARGURA_CABECALHO - strlen(titulo) - 3);
    printf("\n");
}

void ler_data(Data *data)
{
    printf("- Data (d/m/a):    ");
    scanf(" %d/%d/%d", &data->dia, &data->mes, &data->ano);
}

Cliente *perguntar_cliente(Locadora *locadora)
{
    char cnh[TAMANHO_CNH];

    printf("- CNH:             ");
    scanf(" %20[^\n]", cnh);

    Cliente *cliente = buscar_cliente(locadora->clientes, cnh);

    if (cliente == NULL)
    {
        printf("ERRO: A CNH '%s' não está cadastrada no banco de clientes.\n", cnh);
    }

    return cliente;
}

Veiculo *perguntar_veiculo(Locadora *locadora)
{
    char placa[TAMANHO_PLACA];

    printf("- Placa:           ");
    scanf(" %20[^\n]", placa);

    Veiculo *veiculo = buscar_veiculo(locadora->veiculos, placa);

    if (veiculo == NULL)
    {
        printf("ERRO: A placa '%s' não está cadastrada no banco de veículos.\n", placa);
    }

    return veiculo;
}

Data *perguntar_data_de_retirada(Locadora *locadora, Veiculo *veiculo)
{
    Data *data = criar_data();
    bool valida = false;
    
    while (!valida)
    {
        ler_data(data);

        if (existe_locacao_em_data(locadora->locacoes, veiculo->placa, data, data))
        {
            printf("ERRO: O veículo já foi alugado nesta data.\n");
            continue;
        }

        valida = true;
    }

    return data;
}

Data *perguntar_data_de_devolucao(Locadora *locadora, Locacao *locacao)
{
    Data *data = criar_data();
    bool valida = false;
    
    while (!valida)
    {
        ler_data(data);

        if (diferenca_em_dias(locacao->data_de_retirada, data) < 0)
        {
            printf("ERRO: A data de devolução precisa ser após a data de retirada.\n");
            continue;
        }

        if (existe_locacao_em_data(locadora->locacoes, locacao->veiculo->placa, locacao->data_de_retirada, data))
        {
            printf("ERRO: O veículo já foi alugado nesta data.\n");
            continue;
        }

        valida = true;
    }

    return data;
}

int perguntar_nova_quilometragem(Veiculo *veiculo)
{
    int quilometragem;

    do {
        printf("- Quilometragem:   ");
        scanf(" %d", &quilometragem);

        if (quilometragem < veiculo->quilometragem)
        {
            printf("ERRO: A nova quilometragem precisa ser maior que a anterior.\n");
        }
    } while (quilometragem < veiculo->quilometragem);

    return quilometragem;
}

void opcao_cadastrar_veiculo(Locadora *locadora)
{
    imprimir_cabecalho("Cadastro de Veículo");

    Veiculo *veiculo = criar_veiculo(&locadora->veiculos);

    if (veiculo == NULL)
    {
        printf("ERRO: Ocorreu um problema ao alocar o veículo.\n");
        return;
    }

    printf("- Placa:           ");
    scanf(" %20[^\n]", veiculo->placa);

    printf("- Marca:           ");
    scanf(" %100[^\n]", veiculo->marca);

    printf("- Modelo:          ");
    scanf(" %100[^\n]", veiculo->modelo);

    printf("- Ano:             ");
    scanf(" %d", &veiculo->ano);

    printf("- Quilometragem:   ");
    scanf(" %d", &veiculo->quilometragem);

    printf("- Diária:          R$ ");
    scanf(" %lf", &veiculo->diaria);

    veiculo->disponivel = true;
}

void opcao_listar_veiculos(Locadora *locadora)
{
    imprimir_cabecalho("Veículos");
    imprimir_todos_veiculos(locadora->veiculos);
}

void opcao_cadastrar_cliente(Locadora *locadora)
{
    imprimir_cabecalho("Cadastro de Cliente");

    Cliente *cliente = criar_cliente(&locadora->clientes);

    if (cliente == NULL)
    {
        printf("ERRO: Ocorreu um problema ao alocar o cliente.\n");
        return;
    }

    printf("- CNH:             ");
    scanf(" %20[^\n]", cliente->cnh);

    printf("- Nome:            ");
    scanf(" %100[^\n]", cliente->nome);

    printf("- Telefone:        ");
    scanf(" %20[^\n]", cliente->telefone);
}

void opcao_listar_clientes(Locadora *locadora)
{
    imprimir_cabecalho("Clientes");
    imprimir_todos_clientes(locadora->clientes);
}

void opcao_realizar_locacao(Locadora *locadora)
{
    imprimir_cabecalho("Alugar Veículo");

    Veiculo *veiculo = perguntar_veiculo(locadora);

    if (veiculo == NULL)
    {
        return;
    }

    if (!veiculo->disponivel)
    {
        printf("ERRO: O veículo ja está locado no momento.\n");
        return;
    }

    Cliente *cliente = perguntar_cliente(locadora);

    if (cliente == NULL)
    {
        return;
    }

    Data *data = perguntar_data_de_retirada(locadora, veiculo);

    alugar_veiculo(&locadora->locacoes, veiculo, cliente, data);
}

void opcao_devolver_veiculo(Locadora *locadora)
{
    imprimir_cabecalho("Devolver Veículo");

    Veiculo *veiculo = perguntar_veiculo(locadora);

    if (veiculo == NULL)
    {
        return;
    }

    Locacao *locacao = buscar_locacao_em_andamento(locadora->locacoes, veiculo->placa);

    if (locacao == NULL)
    {
        printf("ERRO: O veículo não está locado no momento.\n");
        return;
    }

    Data *data = perguntar_data_de_devolucao(locadora, locacao);
    int quilometragem = perguntar_nova_quilometragem(locacao->veiculo);

    devolver_veiculo(locacao, data, quilometragem);

    printf("\n");
    printf("- Total a pagar:   R$ %.2lf\n", locacao->total);
}

void opcao_listar_locacoes(Locadora *locadora)
{
    imprimir_cabecalho("Locações");
    imprimir_todas_locacoes(locadora->locacoes);
}

void opcao_listar_locacoes_ativas(Locadora *locadora)
{
    imprimir_cabecalho("Locações Ativas");
    imprimir_locacoes_em_andamento(locadora->locacoes);
}

void opcao_listar_locacoes_de_cliente(Locadora *locadora)
{
    imprimir_cabecalho("Locações de Cliente");

    Cliente *cliente = perguntar_cliente(locadora);

    if (cliente == NULL)
    {
        return;
    }

    imprimir_locacoes_de_cliente(locadora->locacoes, cliente->cnh);
}

void opcao_listar_faturamento_mensal(Locadora *locadora)
{
    imprimir_cabecalho("Faturamento");

    int mes, ano;

    printf("- Mês:             ");
    scanf(" %d", &mes);

    printf("- Ano:             ");
    scanf(" %d", &ano);

    double faturamento = contabilizar_faturamento(locadora->locacoes, mes, ano);

    printf("\n");
    printf("- Faturamento:     R$ %.2lf\n", faturamento);
}

void opcao_listar_veiculos_mais_rodados(Locadora *locadora)
{
    imprimir_cabecalho("Mais Rodados");

    Veiculo *vetor[TAMANHO_VEICULOS_MAIS_RODADOS];
    separar_veiculos_mais_rodados(locadora->veiculos, vetor, TAMANHO_VEICULOS_MAIS_RODADOS);

    for (int i = 0; i < TAMANHO_VEICULOS_MAIS_RODADOS; i++)
    {
        if (vetor[i] == NULL)
        {
            break;
        }

        printf("%d. %d km\n", i + 1, vetor[i]->quilometragem);
        printf("   ");
        imprimir_resumo_do_veiculo(vetor[i]);
    }
}

void opcao_listar_veiculos_disponiveis(Locadora *locadora)
{
    imprimir_cabecalho("Veículos Disponíveis");
    imprimir_veiculos_disponiveis(locadora->veiculos);
}

void opcao_ajuda()
{
    printf("» Menu:\n");
    printf("Ações:\n");
    printf("  1. cadastrar veículo\n");
    printf("  2. listar veículos\n");
    printf("  3. cadastrar cliente\n");
    printf("  4. listar clientes\n");
    printf("  5. realizar locação\n");
    printf("  6. devolver veículo\n");
    printf("  7. listar locações\n");
    printf("\n");
    printf("Relatórios:\n");
    printf("  a. listar locações ativas\n");
    printf("  b. listar locações de cliente\n");
    printf("  c. listar faturamento mensal\n");
    printf("  d. listar veículos com maiores quilometragens\n");
    printf("  e. listar veículos disponíveis\n");
    printf("\n");
    printf("  h. ajuda\n");
    printf("  0. sair\n");
}

void menu(Locadora *locadora)
{
    char opcao;

    do
    {
        printf("$ O que você deseja fazer ('h' para ajuda)? ");
        scanf(" %c", &opcao);

        switch (opcao)
        {
        case '0':
            break;
        case '1':
            opcao_cadastrar_veiculo(locadora);
            break;
        case '2':
            opcao_listar_veiculos(locadora);
            break;
        case '3':
            opcao_cadastrar_cliente(locadora);
            break;
        case '4':
            opcao_listar_clientes(locadora);
            break;
        case '5':
            opcao_realizar_locacao(locadora);
            break;
        case '6':
            opcao_devolver_veiculo(locadora);
            break;
        case '7':
            opcao_listar_locacoes(locadora);
            break;
        case 'a':
            opcao_listar_locacoes_ativas(locadora);
            break;
        case 'b':
            opcao_listar_locacoes_de_cliente(locadora);
            break;
        case 'c':
            opcao_listar_faturamento_mensal(locadora);
            break;
        case 'd':
            opcao_listar_veiculos_mais_rodados(locadora);
            break;
        case 'e':
            opcao_listar_veiculos_disponiveis(locadora);
            break;
        case 'h':
            opcao_ajuda();
            break;
        default:
            printf("ERRO: Opção inválida.\n");
            break;
        }

        printf("\n");
    } while (opcao != '0');
}