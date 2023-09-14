#include "menu.h"

#define NUMERO_VEICULOS_MAIS_RODADOS 3

void cadastrar_veiculo(Locadora *locadora)
{
    Veiculo veiculo;

    printf("\nCadastro de Veiculos:\n");

    printf("Digite a placa do veiculo: ");
    scanf(" %10s", veiculo.placa);

    printf("Digite a marca do veiculo: ");
    scanf(" %100[^\n]", veiculo.marca);

    printf("Digite o modelo do veiculo: ");
    scanf(" %100[^\n]", veiculo.modelo);

    printf("Digite o ano de fabricacao do veiculo: ");
    scanf("%d", &veiculo.ano_de_fabricacao);

    printf("Digite o valor da diaria do veiculo: ");
    scanf("%lf", &veiculo.diaria);

    printf("Digite a quilometragem do veiculo: ");
    scanf("%d", &veiculo.quilometragem);

    veiculo.disponivel = true;

    locadora->veiculos = inserir_veiculo(locadora->veiculos, &veiculo);
}

void listar_veiculos(Locadora *locadora)
{
    printf("\nVeiculos:\n");
    imprimir_veiculos(locadora->veiculos);
}

void cadastrar_cliente(Locadora *locadora)
{
    Cliente cliente;

    printf("\nCadastro de Clientes:\n");

    printf("Digite a CNH do cliente: ");
    scanf(" %20[^\n]", cliente.cnh);

    printf("Digite o nome do cliente: ");
    scanf(" %100[^\n]", cliente.nome);

    printf("Digite o telefone do cliente: ");
    scanf(" %20[^\n]", cliente.telefone);

    locadora->clientes = inserir_cliente(locadora->clientes, &cliente);
}

void listar_clientes(Locadora *locadora)
{
    printf("\nClientes:\n");
    imprimir_clientes(locadora->clientes);
}

void realizar_locacao(Locadora *locadora)
{
    char placa[TAMANHO_PLACA + 1];
    char cnh[TAMANHO_CNH + 1];

    printf("\nRealizar locacao:\n");

    printf("Digite a placa do veiculo: ");
    scanf(" %10s", placa);

    Veiculo *veiculo = buscar_veiculo(locadora->veiculos, placa);

    if (veiculo == NULL)
    {
        printf("Nenhum veiculo com a placa %s foi encontrado\n", placa);
        return;
    }

    if (!veiculo->disponivel)
    {
        printf("O veiculo de placa %s nao esta disponivel.\n", placa);
        return;
    }

    printf("Digite a CNH do cliente: ");
    scanf(" %20s", cnh);

    Cliente *cliente = buscar_cliente(locadora->clientes, cnh);

    if (cliente == NULL)
    {
        printf("Nenhum cliente com a CNH %s foi encontrado.\n", cnh);
        return;
    }

    Data data;

    printf("Digite a data de inicio da locacao (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);

    locadora->locacoes = alugar_veiculo(locadora->locacoes, veiculo, cliente, data);
}

void realizar_devolucao(Locadora *locadora)
{
    char placa[TAMANHO_PLACA + 1];

    printf("\nRealizar devolucao:\n");

    printf("Digite a placa do veiculo: ");
    scanf(" %10s", placa);

    Locacao *locacao = buscar_locacao_ativa(locadora->locacoes, placa);

    if (locacao == NULL)
    {
        printf("Nenhuma locacao ativa para o veiculo de placa %s foi encontrada\n", placa);
        return;
    }

    Data data;

    printf("Digite a data de fim da locacao (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);

    int quilometragem;

    printf("Digite a nova quilometragem do veiculo: ");
    scanf("%d", &quilometragem);

    devolver_veiculo(locacao, data, quilometragem);
}

void listar_locacoes_ativas(Locadora *locadora)
{
    printf("\nLocacoes ativas:\n");
    imprimir_locacoes_ativas(locadora->locacoes);
}

void listar_locacoes_de_cliente(Locadora *locadora)
{
    char cnh[TAMANHO_CNH + 1];

    printf("\nLocacoes de um cliente:\n");

    printf("Digite a CNH do cliente: ");
    scanf(" %20s", cnh);

    Cliente *cliente = buscar_cliente(locadora->clientes, cnh);

    if (cliente == NULL)
    {
        printf("Nenhum cliente com a CNH %s foi encontrado\n", cnh);
        return;
    }

    printf("\nLocacoes de %s:\n", cliente->nome);
    imprimir_locacoes_de_cliente(locadora->locacoes, cnh);
}

void contabilizar_faturamento_mensal(Locadora *locadora)
{
    int mes, ano;

    printf("\nFaturamento mensal:\n");
    printf("Digite o mes/ano: ");
    scanf("%d/%d", &mes, &ano);

    double faturamento = calcular_faturamento_de_locacoes(locadora->locacoes, mes, ano);

    printf("O faturamento de %02d/%04d foi de R$%.2lf.\n", mes, ano, faturamento);
}

void listar_veiculos_mais_rodados(Locadora *locadora)
{
    Veiculo *veiculos[NUMERO_VEICULOS_MAIS_RODADOS];
    obter_veiculos_mais_rodados(locadora->veiculos, veiculos, NUMERO_VEICULOS_MAIS_RODADOS);

    printf("\nVeiculos mais rodados:\n");

    for (int i = 0; i < NUMERO_VEICULOS_MAIS_RODADOS; i++)
    {
        if (veiculos[i] == NULL)
        {
            break;
        }

        printf("%d (%d km). ", i + 1, veiculos[i]->quilometragem);
        imprimir_veiculo_resumido(veiculos[i]);
    }
}

void listar_veiculos_disponiveis(Locadora *locadora)
{
    printf("\nVeiculos disponiveis:\n");
    imprimir_veiculos_disponiveis(locadora->veiculos);
}

void imprimir_menu()
{
    printf("\n========== Menu ==========\n");
    printf("Acoes:\n");
    printf("1. cadastrar veiculo.\n");
    printf("2. listar veiculos.\n");
    printf("3. cadastrar cliente.\n");
    printf("4. listar clientes.\n");
    printf("5. realizar locacao.\n");
    printf("6. realizar devolucao.\n");

    printf("\nRelatorios:\n");
    printf("a. listar locacoes ativas.\n");
    printf("b. listar locacoes de um cliente.\n");
    printf("c. contabilizar faturamento mensal.\n");
    printf("d. listar veiculos mais rodados.\n");
    printf("e. listar veiculos disponiveis.\n");
    printf("\n");
    printf("0. sair\n");
    printf("\n");
}

void menu(Locadora *locadora)
{
    char opcao;

    do
    {
        imprimir_menu();

        printf("O que voce deseja fazer? ");
        scanf(" %c", &opcao);

        switch (opcao)
        {
        case '0':
            break;
        case '1':
            cadastrar_veiculo(locadora);
            break;
        case '2':
            listar_veiculos(locadora);
            break;
        case '3':
            cadastrar_cliente(locadora);
            break;
        case '4':
            listar_clientes(locadora);
            break;
        case '5':
            realizar_locacao(locadora);
            break;
        case '6':
            realizar_devolucao(locadora);
            break;
        case 'a':
            listar_locacoes_ativas(locadora);
            break;
        case 'b':
            listar_locacoes_de_cliente(locadora);
            break;
        case 'c':
            contabilizar_faturamento_mensal(locadora);
            break;
        case 'd':
            listar_veiculos_mais_rodados(locadora);
            break;
        case 'e':
            listar_veiculos_disponiveis(locadora);
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao != '0');
}