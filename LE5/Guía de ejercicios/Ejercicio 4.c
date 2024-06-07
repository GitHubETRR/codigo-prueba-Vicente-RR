/*
1) unsigned char es válido. Ocupa 8 bits y va (en decimal) de 0 a 255
2) long char no es válido porque en teoría sería un número entero de 16 bits, pero eso es un short int.
3) unsigned float no es válido.
4) double char no es válido porque double corresponde a un flotante de precisión doble, pero char es para números enteros de 8 bits.
5) signed long es válido. Ocupa 64 bits en OnlineGDB
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
