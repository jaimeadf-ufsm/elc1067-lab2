#include "data.h"

Data *criar_data(Data *data)
{
    return (Data *)calloc(1, sizeof(Data));
}

Data *menor_data(Data *data1, Data *data2)
{
    return diferenca_em_dias(data1, data2) >= 0 ? data1 : data2;
}

Data *maior_data(Data *data1, Data *data2)
{
    return diferenca_em_dias(data1, data2) <= 0 ? data1 : data2;
}

bool existe_sobreposicao_entre_datas(Data *inicio1, Data *fim1, Data *inicio2, Data *fim2)
{
    Data *maior_inicio = maior_data(inicio1, inicio2);
    Data *menor_fim = menor_data(fim1, fim2);

    return diferenca_em_dias(maior_inicio, menor_fim) >= 0;
}

int diferenca_em_dias(Data *data1, Data *data2)
{
    int dias1 = data1->ano * 365 + data1->dia;
    int dias2 = data2->ano * 365 + data2->dia;

    dias1 += data1->ano / 4 - data1->ano / 100 + data1->ano / 400;
    dias2 += data2->ano / 4 - data2->ano / 100 + data2->ano / 400;

    int dias_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 1; i < data1->mes; i++)
    {
        dias1 += dias_mes[i];
    }

    for (int i = 1; i < data2->mes; i++)
    {
        dias2 += dias_mes[i];
    }

    if (data1->mes <= 2 && (data1->ano % 4 == 0 && (data1->ano % 100 != 0 || data1->ano % 400 == 0)))
    {
        dias1--;
    }

    if (data2->mes <= 2 && (data2->ano % 4 == 0 && (data2->ano % 100 != 0 || data2->ano % 400 == 0)))
    {
        dias2--;
    }

    int diferenca = dias2 - dias1;

    return diferenca;
}

void imprimir_data(Data *data)
{
    printf("%02d/%02d/%04d\n", data->dia, data->mes, data->ano);
}