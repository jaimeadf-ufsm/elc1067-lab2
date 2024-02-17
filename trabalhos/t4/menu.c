#include "menu.h"

void imprimir_titulo(char *texto) {
    printf("»»»» %-20s »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»\n", texto);
}

void imprimir_menu() {
    printf("> Menu:\n");
    printf("  1. chegar ao restaurante\n");
    printf("  2. sair do restaurante\n");
    printf("  3. desistir de esperar\n");
    printf("  4. arrumar mesa\n");
    printf("  5. repor pratos\n");
    printf("\n");
    printf("  a. verificar pilha de pratos\n");
    printf("  b. verificar fila de espera\n");
    printf("  c. verificar ocupação\n");
    printf("\n");
    printf("  h. ajuda\n");
    printf("  0. sair\n");
    printf("\n");
}

Mesa *perguntar_mesa(Restaurante *restaurante) {
    int numero;

    printf("- Qual é o número da mesa? ");
    scanf("%d", &numero);

    Mesa *mesa = encontrar_mesa_por_numero(restaurante->salao, numero);

    if (mesa == NULL) {
        printf("• A mesa de número %d não faz parte do salão do restaurante.\n", numero);
    }

    return mesa;
}

void opcao_chegar_ao_restaurante(Restaurante *restaurante) {
    imprimir_titulo("Recepção");
    
    int pessoas;
    
    printf("- Qual é o número de pessoas do grupo? ");
    scanf("%d", &pessoas);

    chegar_ao_restaurante(restaurante, pessoas);
}

void opcao_sair_do_restaurante(Restaurante *restaurante) {
    imprimir_titulo("Saída");

    Mesa *mesa = perguntar_mesa(restaurante);

    if (mesa == NULL) {
        return;
    }

    printf("> Liberando mesa...\n");
    if (!liberar_mesa(restaurante, mesa)) {
        return;
    }

    printf("> Arrumando mesa...\n");
    if (!arrumar_mesa(restaurante, mesa)) {
        return;
    }

    printf("> Chamando da fila de espera...\n");
    chamar_da_fila_de_espera(restaurante, mesa);
}

void opcao_arrumar_mesa(Restaurante *restaurante) {
    imprimir_titulo("Arrumar Mesa");

    Mesa *mesa = perguntar_mesa(restaurante);

    if (mesa == NULL) {
        return;
    }

    printf("> Arrumando mesa...\n");
    if (!arrumar_mesa(restaurante, mesa)) {
        return;
    }

    printf("> Chamando da fila de espera...\n");
    chamar_da_fila_de_espera(restaurante, mesa);
}

void opcao_desistir_de_esperar(Restaurante *restaurante) {
    imprimir_titulo("Desistir da Fila");

    int senha;

    printf("- Qual a senha do grupo? ");
    scanf("%d", &senha);

    if (!sair_da_fila(restaurante->fila, senha)) {
        printf("• O grupo %d não está na fila de espera.\n", senha);
        return;
    }
    printf("• O grupo %d foi retirado da fila.\n", senha);
}


void opcao_repor_pratos(Restaurante *restaurante) {
    imprimir_titulo("Limpar Pratos");

    int n;

    printf("- Quantos pratos serão repostos na pilha? ");
    scanf("%d", &n);

    restaurante->pratos = empilhar_pratos(restaurante->pratos, n);

    printf("• A pilha de pratos agora possui %d prato(s).\n", contar_pratos(restaurante->pratos));
}

void opcao_verificar_pratos(Restaurante *restaurante) {
    imprimir_titulo("Pratos");
    printf("• A pilha possui %d prato(s) limpo(s).\n", contar_pratos(restaurante->pratos));
}

void opcao_verificar_fila(Restaurante *restaurante) {
    imprimir_titulo("Fila de Espera");
    imprimir_fila(restaurante->fila);
}

void opcao_verificar_ocupacao(Restaurante *restaurante) {
    imprimir_titulo("Ocupação");

    int numero;

    printf("- Qual é o número da mesa (-1 para todas)? ");
    scanf("%d", &numero);

    if (numero == -1) {
        imprimir_salao(restaurante->salao);
        return;
    }

    Mesa *mesa = encontrar_mesa_por_numero(restaurante->salao, numero);

    if (mesa == NULL) {
        printf("• A mesa de número %d não faz parte do salão do restaurante.\n", numero);
        return;
    }

    imprimir_mesa(restaurante->salao, mesa);
}

void menu(Restaurante *restaurante) {
    char opcao;

    imprimir_menu();

    do {
        printf("$ O que você deseja fazer ('h' para ajuda)? ");
        scanf(" %c", &opcao);

        switch (opcao)
        {
        case '0':
            break;
        case '1':
            opcao_chegar_ao_restaurante(restaurante);
            break;
        case '2':
            opcao_sair_do_restaurante(restaurante);
            break;
        case '3':
            opcao_desistir_de_esperar(restaurante);
            break;
        case '4':
            opcao_arrumar_mesa(restaurante);
            break;
        case '5':
            opcao_repor_pratos(restaurante);
            break;
        case 'a':
            opcao_verificar_pratos(restaurante);
            break;
        case 'b':
            opcao_verificar_fila(restaurante);
            break;
        case 'c':
            opcao_verificar_ocupacao(restaurante);
            break;
        case 'h':
            imprimir_menu();
            break;
        default:
            printf("• Opção inválida.\n");
            break;
        }

        printf("\n");
    } while (opcao != '0');
}
