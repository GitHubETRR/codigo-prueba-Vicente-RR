#include <stdio.h>

int main()
{
    float base;
    float altura;
    float area;
    float perimetro;
    do
    {
        printf("¿Cuánto mide la base del rectángulo?\n");
        scanf("%f",&base);
    } while (base<=0);
    do
    {
        printf("¿Cuánto mide la altura del rectángulo?\n");
        scanf("%f",&altura);
    } while (altura<=0);
    area=base*altura;
    perimetro=(base+altura)*2;
    printf("Área: %f\nPerímetro: %f",area,perimetro);
    return 0;
}
