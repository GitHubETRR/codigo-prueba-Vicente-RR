#include <stdio.h>

int main()
{
  float cm, pulgadas;
  int pies;
  printf("Introducí los centímetros: ");
  scanf("%f", &cm);
  pulgadas = cm/2.54;
  pies = (int) pulgadas/12;
  pulgadas -= pies*12;
  if (cm==1.0) printf("%f centímetro equivale", cm);
  else printf("%f centímetros equivalen", cm);
  printf(" a %i pie", pies);
  if ((pies!=1)&&(pies!=-1)) printf("s");
  printf(" y %f pulgada", pulgadas);
  if ((pulgadas!=1)&&(pulgadas!=-1)) printf("s");
  return 0;
}
