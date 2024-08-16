#include <stdio.h>

#define JUGADORES 2
#define CASILLEROS 10
#define AGUA 0
#define PORTAVIONES 1
#define DESTRUCTOR_A 2
#define DESTRUCTOR_B 3
#define PATRULLERO_A 4
#define PATRULLERO_B 5
#define DISPARO 6
#define BAJADO_VERTICAL 12
#define BAJADO_HORIZONTAL 13
#define CARACTER_AGUA 'O'
#define CARACTER_DISPARO 'X'
#define CARACTER_VERTICAL '/'
#define CARACTER_HORIZONTAL '~'
#define CANTIDAD_DE_BARCOS 5
#define CARACTERES_NOMBRES_BARCOS 13

void vaciarTablero(int[JUGADORES][CASILLEROS][CASILLEROS]);
void imprimirTablero(int[JUGADORES][CASILLEROS][CASILLEROS],int);
void armarTablero(int[JUGADORES][CASILLEROS][CASILLEROS],int);

int main()
{
    int tablero[JUGADORES][CASILLEROS][CASILLEROS];
    
    vaciarTablero(tablero);
    imprimirTablero(tablero,0);
    
    return 0;
}

void vaciarTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        for (int columna=0; columna<CASILLEROS; columna++)
        {
            for (int fila=0; fila<CASILLEROS; fila++)
            {
                tablero[jugador][columna][fila] = AGUA;
            }
        }
    }
}

void imprimirTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS], int jugador)
{
    printf(" |0|1|2|3|4|5|6|7|8|9");
    for (int fila=0; fila<CASILLEROS; fila++)
    {
        printf("\n---------------------\n");
        printf("%i", fila);
        for (int columna=0; columna<CASILLEROS; columna++)
        {
            int c=tablero[jugador][columna][fila];
            char caracterCasillero;
            if ((c==AGUA)||(c==PORTAVIONES)||(c==DESTRUCTOR_A)||(c==DESTRUCTOR_B)||(c==PATRULLERO_A)||(c==PATRULLERO_B)) caracterCasillero=' ';
            if (c==(DISPARO+AGUA)) caracterCasillero=CARACTER_AGUA;
            if ((c>(DISPARO+AGUA))&&(c<BAJADO_VERTICAL)) caracterCasillero=CARACTER_DISPARO;
            if (c==BAJADO_VERTICAL) caracterCasillero=CARACTER_VERTICAL;
            if (c==BAJADO_HORIZONTAL) caracterCasillero=CARACTER_HORIZONTAL;
            printf("|%c",caracterCasillero);
        }
    }
}

void armarTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS], int jugador)
{
    char nombreBarco[CANTIDAD_DE_BARCOS][CARACTERES_NOMBRES_BARCOS] = {"PORTAVIONES","DESTRUCTOR A","DESTRUCTOR B","PATRULLERO A","PATRULLERO_B"};
    for (int barco=0; barco<CANTIDAD_DE_BARCOS; barco++)
    {
        
    }
}
