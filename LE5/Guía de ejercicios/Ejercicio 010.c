//Programa 1 (falta una parte del código)
#include <stdio.h>

int main(){
    int n,total;
    float promedio;
    n=0; //Acá debería preguntar la cantidad de números a sumar y realizar la suma, guardándola en el total
    promedio=total/n; //En esta operación no hay ni un total ni la cantidad de números (siempre es 0). Además, la división entre dos enteros no da un float, y esto se puede solucionar poniendo (float) para pasar momentáneamente los int a float
    printf("Prom=%f\n",promedio);
    return 0;
}
//Programa 2 (todo mal)
#include <stdio.h>

int main(void){
    integer x; //int
    real y; //float/double
    scanf ("%d",y); //Se intenta leer la variable real (que debería ser float o double) como entero. También falta el &
    printf("%f",x) //Se intenta printear la variable entera como float. También falta el ;
    return 0;
}
