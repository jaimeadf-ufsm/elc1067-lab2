#include <stdio.h>

#define NUM 5

struct retangulo
{
    float base;
    float altura;
    float perimetro;
    float area;
};

typedef struct retangulo Retangulo;

void lerRetangulos(Retangulo retangulos[NUM])
{
    for (int i = 0; i < NUM; i++)
    {
        printf("Digite a base e a altura para o retangulo %d: ", i + 1);
        scanf("%f %f", &retangulos[i].base, &retangulos[i].altura);
    }
}

void calculaPeriArea(Retangulo ret)
{
    ret.perimetro = 2 * ret.base + 2 * ret.altura;
    ret.area = ret.base * ret.altura;

    printf("Base: %f\n", ret.base);
    printf("Altura: %f\n", ret.altura);
    printf("Area: %f\n", ret.area);
    printf("Perimetro: %f\n\n", ret.perimetro);
}

int main()
{
    Retangulo retangulos[NUM];
    
    lerRetangulos(retangulos);
    
    for (int i = 0; i < NUM; i++)
    {
        printf("Retangulo %d:\n", i + 1);
        calculaPeriArea(retangulos[i]);
    }

    return 0;
}