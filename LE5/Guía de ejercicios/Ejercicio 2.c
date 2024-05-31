/*
1) a vale 5
2) a vale 5
3) a vale 5
4) a vale 0.000000
5) a vale ♣ //(depende del sistema)
6) b vale (basura)
7) b vale (basura)
8) b vale 13.546000
9) b vale 13.5
10) b vale 13.55
11) b vale 13.5460
12) b vale    13.5
13) b vale 
14) b vale (basura)
15) b vale (basura)
16) c vale 65
17) c vale 0.000000
18) c vale A
19) c vale 101
20) c vale 41
21) d vale 97
22) d vale 0.000000
23) d vale a
24) d vale 141
25) d vale 61
CÓDIGO PARA COMPROBAR:
*/
#include <stdio.h>

int a=5;
float b=13.546;
char c='A';
char d='a';

int main()
{
  printf ("a vale %d \n", a);
  printf ("a vale %o \n", a);
  printf ("a vale %X \n", a);
  printf ("a vale %f \n", a);
  printf ("a vale %c \n", a);
  printf ("b vale %d \n", b);
  printf ("b vale %5.2d \n", b);
  printf ("b vale %f \n", b);
  printf ("b vale %.1f \n", b);
  printf ("b vale %.2f \n", b);
  printf ("b vale %6.4f \n", b);
  printf ("b vale %6.1f \n", b);
  printf ("b vale %c \n", b);
  printf ("b vale %o \n", b);
  printf ("b vale %X \n", b);
  printf ("c vale %d \n", c);
  printf ("c vale %f \n", c);
  printf ("c vale %c \n", c);
  printf ("c vale %o \n", c);
  printf ("c vale %X \n", c);
  printf ("d vale %d \n", d);
  printf ("d vale %f \n", d);
  printf ("d vale %c \n", d);
  printf ("d vale %o \n", d);
  printf ("d vale %X \n", d);
}
