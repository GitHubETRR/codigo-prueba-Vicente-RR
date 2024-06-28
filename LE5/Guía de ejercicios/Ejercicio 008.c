/*
1) a % b * c + 1 = 13
2) a % (b * c ) + 1 = 5
3) 24 / c * 4 = 32
4) (int) (a / b ) % 2 = 1
5) 48 / (c*2) * 4 = 32
CÓDIGO PARA COMPROBAR:
*/
int main()
{
  int a=49, b=5, c=3;
  printf("1) %i \n", a % b * c + 1);
  printf("2) %i \n", a % (b * c ) + 1);
  printf("3) %i \n", 24 / c * 4);
  printf("4) %i \n", (a / b ) % 2);
  printf("5) %i \n", 48 / (c*2) * 4);
  return 0;
}
