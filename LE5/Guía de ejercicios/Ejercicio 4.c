/*
1) unsigned char es válido. Ocupa 8 bits y permite valores de 0 a 255
2) long char no es válido porque en teoría sería un número entero de 16 bits, pero eso es un short int.
3) unsigned float no es válido.
4) double char no es válido porque double corresponde a un flotante de precisión doble, pero char es para números enteros de 8 bits.
5) signed long es válido. Ocupa 64 bits en OnlineGDB y 32 en la consola de Windows, y permite valores negativos y positivos (el rango depende del sistema).
6) unsigned short es válido. Ocupa 16 bits y permite valores de 0 a 65535.
7) signed long int es válido, y es lo mismo que signed long.
8) long double es válido. Ocupa 128 bits en OnlinegDB y 96 en la consola de Windows, y permite valores flotantes negativos y positivos (el rango depende del sistema).
9) long bool no es válido. Las variables booleanas siempre ocupan lo mismo porque tienen solo 2 posibles estados.
CÓDIGO 1 PARA COMPROBAR (revisando los errores):
*/
int main()
{
    unsigned char a;
    long char b;
    unsigned float c;
    double char d;
    signed long e;
    unsigned short f;
    signed long int g;
    long double h;
    long bool i;
}
//CÓDIGO 2 PARA COMPROBAR:
#include <stdio.h>

int main()
{
    printf("%d\n", sizeof(unsigned char));
    printf("%d\n", sizeof(signed long));
    printf("%d\n", sizeof(unsigned short));
    printf("%d\n", sizeof(signed long));
    printf("%d\n", sizeof(long double));
}
