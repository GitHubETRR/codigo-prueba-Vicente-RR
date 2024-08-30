#include <stdio.h>
#include <stdbool.h>

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
#define TECLA0 '1'
#define TECLA1 '2'
#define TAMAÑO_PORTAVIONES 5
#define TAMAÑO_DESTRUCTOR 3
#define TAMAÑO_PATRULLERO 2

void VaciarTablero(int[JUGADORES][CASILLEROS][CASILLEROS]);
void ImprimirTablero(int[JUGADORES][CASILLEROS][CASILLEROS],int);
void ArmarTablero(int[JUGADORES][CASILLEROS][CASILLEROS],int,bool);
char PedirDireccion(char[CANTIDAD_DE_BARCOS][CARACTERES_NOMBRES_BARCOS], int);
char Respuesta(void);
void PedirCoordenadas(char);

int main()
{
    int tablero[JUGADORES][CASILLEROS][CASILLEROS];
    
    VaciarTablero(tablero);
    
    
    return 0;
}

void VaciarTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS])
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

void ImprimirTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS], int jugador, bool mostrarBarcos)
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
            if (c==AGUA) caracterCasillero=' ';
            if (mostrarBarcos)
            {
                if ((c==PORTAVIONES)||(c==DESTRUCTOR_A)||(c==DESTRUCTOR_B)||(c==PATRULLERO_A)||(c==PATRULLERO_B)) caracterCasillero=CARACTER_DISPARO;
            }
            else
            {
                if (c==(DISPARO+AGUA)) caracterCasillero=CARACTER_AGUA;
                if ((c>(DISPARO+AGUA))&&(c<BAJADO_VERTICAL)) caracterCasillero=CARACTER_DISPARO;
                if (c==BAJADO_VERTICAL) caracterCasillero=CARACTER_VERTICAL;
                if (c==BAJADO_HORIZONTAL) caracterCasillero=CARACTER_HORIZONTAL;
            }
            printf("|%c",caracterCasillero);
        }
    }
}

void ArmarTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS], int jugador)
{
    const char nombreBarco[CANTIDAD_DE_BARCOS][CARACTERES_NOMBRES_BARCOS] = {"PORTAVIONES","DESTRUCTOR A","DESTRUCTOR B","PATRULLERO A","PATRULLERO_B"};
    
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        for (int barco=1; barco<(CANTIDAD_DE_BARCOS+1); barco++)
        {
            char direccion;
            int columna;
            int fila;
            
            direccion = PedirDireccion(nombreBarco, barco);
            PedirCoordenadas(barco, tablero, direccion, columna, fila, direccion);
            
        }
    }
}

char PedirDireccion(char nombreBarco[CANTIDAD_DE_BARCOS][CARACTERES_NOMBRES_BARCOS], int barco)
{
    char direccion;
    int casillerosBarco = TamañoBarco(barco);
    
    printf("¿Deseás colocar el %s (de %i casilleros) en vertical (%c) u horizontal (%c)?\n", nombreBarco[barco], casillerosBarco, TECLA0, TECLA1);
    direccion = Respuesta();
    
    return direccion;
}

int TamañoBarco(barco)
{
    int casillerosBarco;
    
    if ((barco)==PORTAVIONES) casillerosBarco=TAMAÑO_PORTAVIONES;
    if (((barco)==DESTRUCTOR_A)||((barco)==DESTRUCTOR_B)) casillerosBarco=TAMAÑO_DESTRUCTOR;
    if (((barco)==PATRULLERO_A)||((barco)==PATRULLERO_B)) casillerosBarco=TAMAÑO_PATRULLERO;

    return casillerosBarco;
}

char Respuesta(void)
{
    char respuesta;
    
    scanf("%c", respuesta);
    fflush(stdin);
    while ((respuesta!=TECLA0)&&(respuesta!=TECLA1))
    {
        printf("Por favor, introducí una respuesta válida\n");
        scanf("%c", respuesta);
        fflush(stdin);
    }
    
    return respuesta;
}

void PedirCoordenadas(int barco, int tablero[JUGADORES][CASILLEROS][CASILLEROS], char direccion, int columna, int fila, char direccion)
{
    printf("Enviá la columna junto con la fila en la que vas a colocar el casillero ");
    if (direccion==TECLA0) printf("superior");
    else printf("izquierdo");
    printf(". Por ejemplo, enviar 47 significa columna 4 fila 7\n");
    RespuestaCoordenadas(barco, tablero, columna, fila, direccion);
}

void RespuestaCoordenadas(int barco, int tablero[JUGADORES][CASILLEROS][CASILLEROS], int columna, int fila, char direccion)
{
    bool coordenadasValidas;
    
    coordenadasValidas = ComprobarCoordenadas(barco, tablero, columna, fila, direccion);
    while (!(coordenadasValidas))
    {
        printf("Por favor, introducí una respuesta válida\n");
        coordenadasValidas = ComprobarCoordenadas(barco, tablero, columna, fila, direccion);
    }
}

bool ComprobarCoordenadas(int barco, int tablero[JUGADORES][CASILLEROS][CASILLEROS], int columna, int fila, char direccion)
{
    bool coordenadasValidas=true;
    int casillerosBarco = TamañoBarco(barco);
    
    scanf("%1i%1i", columna, fila);
    fflush(stdin);
    if ((columna<0)||(columna>=CASILLEROS)||(fila<0)||(fila>=CASILLEROS))
    coordenadasValidas=false;
    //Agregar casilleros adyacentes con un for
    if (direccion==TECLA0) //Vertical
    {
        
    }
    if (direccion==TECLA1) //Horizontal
    {
        
    }
    
    return coordenadasValidas;
}
