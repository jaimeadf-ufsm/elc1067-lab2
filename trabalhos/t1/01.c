#include <stdio.h>

#define PI 3.14159265358979323846

void calc_esfera(float r, float *area, float *volume)
{
    *area = 4.0f * PI * r * r;
    *volume = 4.0f / 3.0f * PI * r * r * r;
}

int main()
{
    float r;
    float area, volume;
 
    printf("Digite o raio da esfera: ");
    scanf("%f", &r);
    calc_esfera(r, &area, &volume);

    printf("Area: %f\n", area);
    printf("Volume: %f\n", volume);

    return 0;
}