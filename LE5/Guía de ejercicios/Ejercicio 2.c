/*
1) a vale 5
2) a vale 5
3) a vale 5
4) a vale 0.0
5) a vale ♣ //(depende del sistema)
//
13,546(10) = 1101,10001011110001101010(2) = 1,10110001011110001101010*2^3 = 1,10110001011110001101010*2^(10000010-01111111)
Como está codificado en IEEE 754, el número es 01000001010110001011110001101010 -> 1096334442(10)
//
6) b vale 
7) b vale 
8) b vale 
9) b vale 
10) b vale 
11) b vale 
12) b vale 
13) b vale 
14) b vale 
15) b vale 
16) c vale 
17) c vale 
18) c vale 
19) c vale 
20) c vale 
21) d vale 
22) d vale 
23) d vale 
24) d vale 
25) d vale 
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
