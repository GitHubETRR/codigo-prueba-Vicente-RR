#include <stdio.h>

int main()
{
  float numero1, numero2, suma, resta, producto, division, promedio, operacionLarga;
  printf("Introducí el primer número ");
  scanf("%f", &numero1);
  printf("Introducí el segundo número ");
  scanf("%f", &numero2);
  suma = numero1+numero2;
  resta = numero1-numero2;
  producto = numero1*numero2;
  division = numero1/numero2;
  promedio = (numero1+numero2)/2;
  operacionLarga = 2*numero1 - numero2/2;
  printf("La suma de tus dos números es %f\n", suma);
  printf("La resta de tus dos números es %f\n", resta);
  printf("El producto de tus dos números es %f\n", producto);
  printf("La división de tus dos números es %f\n", division);
  printf("El promedio de tus dos números es %f\n", promedio);
  printf("El doble producto del primer número menos la mitad del segundo es %f", operacionLarga);
  return 0;
}
