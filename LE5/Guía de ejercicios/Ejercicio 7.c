/*
1) 8 * 6 / 3 * 4 = 64
2) (8 * 6) / 3 * 4 = 64
3) 8 * 6 / (3 * 4) = 4
4) (8 * 6 / 3 * 4) = 64
5) (8 * 6) / (3 * 4) = 4
6) 1 + 4 * 5 + 8 / 4 + 4 = 27
7) 1 + 4 * 5 - 8 / 4 + 4 = 23
CÓDIGO PARA COMPROBAR:
*/
#include <stdio.h>

int main()
{
  printf("1) %i \n", 8 * 6 / 3 * 4);
  printf("2) %i \n", (8 * 6) / 3 * 4);
  printf("3) %i \n", 8 * 6 / (3 * 4));
  printf("4) %i \n", (8 * 6 / 3 * 4));
  printf("5) %i \n", (8 * 6) / (3 * 4));
  printf("6) %i \n", 1 + 4 * 5 + 8 / 4 + 4);
  printf("7) %i \n", 1 + 4 * 5 - 8 / 4 + 4);
}
