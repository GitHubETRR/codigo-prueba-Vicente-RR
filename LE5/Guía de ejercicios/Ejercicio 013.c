#include <stdio.h>

int main()
{
    float precioKG;
    float cantidad;
    float precioTotal;
    do
    {
        printf("¿Cuál es el precio por kg de tu producto?\n");
        scanf("%f",&precioKG);
    } while (precioKG<=0);
    do
    {
        printf("¿Cuántos kg?\n");
        scanf("%f",&cantidad);
    } while (cantidad<=0);
    precioTotal = precioKG*cantidad;
    printf("El precio total es %f",precioTotal);
    return 0;
}
