/*
a) 12
b) 30
c) indeterminación (división por 0)
d) 28
e) -36
CÓDIGO PARA COMPROBAR:
*/
#include <stdio.h>

int main()
{
    int x = 2, y = 6, z = 9, r = 100, s = 10, a = 15, b = 3;
    
    x += 10;
    printf("%i \n", x);
    s *= b;
    printf("%i \n", s);
    /*r /= 0;
    printf("%i \n", r);*/
    y += x + 10;
    printf("%i \n", y);
    z -= a*b;
    printf("%i", z);
    return 0;
}
