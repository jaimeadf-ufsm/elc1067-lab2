#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct data Data;

struct data
{
    int dia;
    int mes;
    int ano;
};

Data *criar_data();

Data *maior_data(Data *data1, Data *data2);
Data *menor_data(Data *data1, Data *data2);

bool existe_sobreposicao_entre_datas(Data *inicio1, Data *fim1, Data *inicio2, Data *fim2);

int diferenca_em_dias(Data *data1, Data *data2);

void imprimir_data(Data *data);

#endif