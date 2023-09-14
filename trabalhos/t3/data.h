#ifndef DATA_H
#define DATA_H

typedef struct data Data;

struct data
{
    int dia;
    int mes;
    int ano;
};

int calcular_diferenca_de_dias(Data data1, Data data2);

#endif