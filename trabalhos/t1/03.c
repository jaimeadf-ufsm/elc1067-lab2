#include <stdio.h>
#include <string.h>

struct triangulo
{
    int ladoA;
    int ladoB;
    int ladoC;
    char ehTriangulo;
    char tipo[20];
};

typedef struct triangulo Triangulo;

void ler_triangulo(Triangulo *triangulo)
{
    printf("Digite tres valores A, B e C para os lados de um triangulo: ");
    scanf("%d %d %d", &triangulo->ladoA, &triangulo->ladoB, &triangulo->ladoC);
}

void verifica_triangulo(Triangulo *triangulo)
{
    if (
        (triangulo->ladoA < triangulo->ladoB + triangulo->ladoC) &&
        (triangulo->ladoB < triangulo->ladoA + triangulo->ladoC) && 
        (triangulo->ladoC < triangulo->ladoA + triangulo->ladoB)
    )
    {
        triangulo->ehTriangulo = 1;
        
        if (
            (triangulo->ladoA != triangulo->ladoB && triangulo->ladoA != triangulo->ladoC) &&
            (triangulo->ladoB != triangulo->ladoC)
        )
        {
            strcpy(triangulo->tipo, "escaleno");
        }
        else if ((triangulo->ladoA == triangulo->ladoB) && (triangulo->ladoA == triangulo->ladoC))
        {
            strcpy(triangulo->tipo, "equilatero");
        }
        else
        {
            strcpy(triangulo->tipo, "isosceles");
        }       
    }
    else
    {
        triangulo->ehTriangulo = 0;
    }
}

void mostrar_resultado_triangulo(Triangulo *triangulo)
{
    if (triangulo->ehTriangulo)
    {
        printf("Os lados %d, %d e %d compoem um triangulo de tipo %s.\n", triangulo->ladoA, triangulo->ladoB, triangulo->ladoC, triangulo->tipo);
    }
    else
    {
        printf("Os lados %d, %d e %d nao formam um triangulo.\n", triangulo->ladoA, triangulo->ladoB, triangulo->ladoC);
    }
}

int main()
{
    Triangulo triangulo;

    ler_triangulo(&triangulo);
    verifica_triangulo(&triangulo);
    mostrar_resultado_triangulo(&triangulo);

    return 0;
}