/*
a) x = 10 + x - y;
  x += 10-y  ✔
  x -= y+10
  x += 10+y
b) r = 100*r;
  r *= 100*r
  r *= 100  ✔
  r += 100
c) y = y/(10+x); 
  y /= 10*x
  y /= 10 + y/x
  y /= 10+x  ✔
d) z = 3 * x + 6; 
  z += 6
  z *= 3
  no es posible  ✔
Esta última operación no es posible usando operadores mixtos porque z no está en la igualdad.
CÓDIGO PARA COMPROBAR:
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int x=rand(), xa, x1, x2, x3, r=rand(), rb, r1, r2, r3, y=rand(), yc, y1, y2, y3, z=rand(), z1, z2;

  xa = 10 + x - y;
  x1 = x+(10-y);
  x2 = x-(y+10);
  x3 = x+(10+y);
  if (xa==x1) printf("a: 1\n");
  if (xa==x2) printf("a: 2\n");
  if (xa==x3) printf("a: 3\n");
  rb = 100*r;
  r1 = r*(100*r);
  r2 = r*100;
  r3 = r+100;
  if (rb==r1) printf("b: 1\n");
  if (rb==r2) printf("b: 2\n");
  if (rb==r3) printf("b: 3\n");
  yc = y/(10+x);
  y1 = y/(10*x);
  y2 = y/(10+y/x);
  y3 = y/(10+x);
  if (yc==y1) printf("c: 1\n");
  if (yc==y2) printf("c: 2\n");
  if (yc==y3) printf("c: 3\n");
  return 0;
}
