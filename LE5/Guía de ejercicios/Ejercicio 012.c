#include <stdio.h>

int main()
{
    int edad;
    int dias;
    do
    {
        printf("¿Cuántos años tenés?\n");
        scanf("%i",&edad);
    } while (edad<0);
    dias = edad*365.25;
    printf("Viviste %i días", dias);
    return 0;
}
