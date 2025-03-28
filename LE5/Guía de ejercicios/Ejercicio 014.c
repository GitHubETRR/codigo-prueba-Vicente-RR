#include <stdio.h>

int main()
{
    float angulo1;
    float angulo2;
    float angulo3;
    do
    {
        printf("¿Cuál es el valor del primer ángulo del triángulo?\n");
        scanf("%f",&angulo1);
    } while ((angulo1<=0)||(angulo1>=180));
    do
    {
        printf("¿Cuál es el valor del segundo ángulo del triángulo?\n");
        scanf("%f",&angulo2);
        angulo3 = 180-angulo1-angulo2;
    } while (angulo3<=0);
    printf("El tercer ángulo es de %f°",angulo3);
    return 0;
}
