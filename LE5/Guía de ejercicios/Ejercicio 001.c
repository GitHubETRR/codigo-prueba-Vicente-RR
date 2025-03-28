/*
int a=3,b=2,c=1, d,e; 
float m=2.5, n=5.4, r,s; 

Operación      Resultado
d=m;           . 2
d=n;           . 5
e=3.7;         . 3
d=a;           . 3
d=a+b;         . 5
d=a/b;         . 1
d=a%b;         . 1
d=a%2;         . 1
e=b/c;         . 2
e=c/b;         . 0
r=a+b;         . 5.0
r=a/b;         . 1.0
r=a/2;         . 1.0
r=a/2.0;       . 1.5
s=m+n;         . 7.9
s=3+4-1;       . 6.0
s=3.0+4.0-1;   . 6.0
a=m;           . 2
a=m/2;         . 1
a=m/2.0;       . 1
a=3.0+4.0-1;   . 6
r=a+1;         . 7.0
r=a+1.0;       . 7.0
a++;           . 7
r++;           . 8.0
b--;           . 1
a+=5;          . 12
s*=5;          . 30.0

CÓDIGO PARA COMPROBAR:
*/
int a=3,b=2,c=1, d,e; 
float m=2.5, n=5.4, r,s; 

#include <stdio.h>

int main()
{
    d=m;
    printf("%i \n", d);
    d=n;
    printf("%i \n", d);
    e=3.7;
    printf("%i \n", e);
    d=a;
    printf("%i \n", d);
    d=a+b;
    printf("%i \n", d);
    d=a/b;
    printf("%i \n", d);
    d=a%b;
    printf("%i \n", d);
    d=a%2;
    printf("%i \n", d);
    e=b/c;
    printf("%i \n", e);
    e=c/b;
    printf("%i \n", e);
    r=a+b;
    printf("%f \n", r);
    r=a/b;
    printf("%f \n", r);
    r=a/2;
    printf("%f \n", r);
    r=a/2.0;
    printf("%f \n", r);
    s=m+n;
    printf("%f \n", s);
    s=3+4-1;
    printf("%f \n", s);
    s=3.0+4.0-1;
    printf("%f \n", s);
    a=m;
    printf("%i \n", a);
    a=m/2;
    printf("%i \n", a);
    a=m/2.0;
    printf("%i \n", a);
    a=3.0+4.0-1;
    printf("%i \n", a);
    r=a+1;
    printf("%f \n", r);
    r=a+1.0;
    printf("%f \n", r);
    a++;
    printf("%i \n", a);
    r++;
    printf("%f \n", r);
    b--;
    printf("%i \n", b);
    a+=5;
    printf("%i \n", a);
    s*=5;
    printf("%f \n", s);
    return 0;
}
