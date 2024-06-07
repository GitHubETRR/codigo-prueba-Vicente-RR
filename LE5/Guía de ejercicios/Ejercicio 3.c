/*
1) Se almacena un número entero enviado por el usuario. Si se envía un número no entero, se almacena la parte entera.
2) Se almacena un número flotante codificado. Por esto, no se va a imprimir el mismo número ingresado.
3) Se almacena el valor en ASCII del caracter introducido.
4) Se almacena el equivalente del entero ingresado codificado como flotante.
5) Se almacena el número flotante introducido.
6) Se almacena el valor ASCII del caracter introducido codificado como flotante. Al ser este un número de solo 8 bits, es tan bajo que siempre se va a imprimir 0.000000.
7-8-9) No se puede saber qué se almacena porque printf no permite imprimirlo. Igualmente, lo que ocurre es que intenta guardar un dato de 32 bits en una variable de 8.
*/
#include <stdio.h>

int main()
{
  int a;
  float b;
  char c;
   
  scanf ("%d", &a);
  printf("%i", a);
  scanf ("%f", &a);
  printf("%i", a);
  scanf ("%c", &a);
  printf("%i", a);
  scanf ("%d", &b);
  printf("%f", b);
  scanf ("%f", &b);
  printf("%f", b);
  scanf ("%c", &b);
  printf("%f", b);
  scanf ("%d", &c);
  printf("%c", c);
  scanf ("%f", &c);
  printf("%c", c);
}
