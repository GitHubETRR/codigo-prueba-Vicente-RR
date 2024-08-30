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
void ImprimirTablero(int[JUGADORES][CASILLEROS][CASILLEROS], int, bool);
void ArmarTablero(int[JUGADORES][CASILLEROS][CASILLEROS]);
char PedirDireccion(int);
char Respuesta(void);
void PedirCoordenadas(int barco, int [JUGADORES][CASILLEROS][CASILLEROS], char, int[2], int);
int TamañoBarco(int);
void RespuestaCoordenadas(int, int [JUGADORES][CASILLEROS][CASILLEROS], int[2], char, int);
bool ComprobarCoordenadas(int, int [JUGADORES][CASILLEROS][CASILLEROS], int[2], char, int);
void AgregarBarco(int, int, int tablero[JUGADORES][CASILLEROS][CASILLEROS], int coordenadas[2], char direccion);
void LimpiarTeclado();

int main()
{
    int tablero[JUGADORES][CASILLEROS][CASILLEROS];
    
    VaciarTablero(tablero);
    ArmarTablero(tablero);
    
    
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
    printf(" |0|1|2|3|4|5|6|7|8|9\n");
    for (int fila=0; fila<CASILLEROS; fila++)
    {
        printf("---------------------\n");
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
        printf("\n");
    }
}

void ArmarTablero(int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        printf("JUGADOR %i\n", jugador);
        for (int barco=1; barco<(CANTIDAD_DE_BARCOS+1); barco++)
        {
            char direccion;
            int coordenadas[2];
            
            ImprimirTablero(tablero, jugador, true);
            direccion = PedirDireccion(barco);
            PedirCoordenadas(barco, tablero, direccion, coordenadas, jugador);
            AgregarBarco(barco, jugador, tablero, coordenadas, direccion);
        }
    }
}

char PedirDireccion(int barco)
{
    char direccion;
    int casillerosBarco = TamañoBarco(barco);
    const char nombreBarco[CANTIDAD_DE_BARCOS][CARACTERES_NOMBRES_BARCOS] = {"PORTAVIONES","DESTRUCTOR A","DESTRUCTOR B","PATRULLERO A","PATRULLERO_B"};
    
    printf("¿Deseás colocar el %s (de %i casilleros) en vertical (%c) u horizontal (%c)?\n", nombreBarco[barco-1], casillerosBarco, TECLA0, TECLA1);
    direccion = Respuesta();
    
    return direccion;
}

int TamañoBarco(int barco)
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
    
    scanf("%c", &respuesta);
    LimpiarTeclado();
    while ((respuesta!=TECLA0)&&(respuesta!=TECLA1))
    {
        printf("Por favor, introducí una respuesta válida\n");
        scanf("%c", &respuesta);
        LimpiarTeclado();
    }
    
    return respuesta;
}

void PedirCoordenadas(int barco, int tablero[JUGADORES][CASILLEROS][CASILLEROS], char direccion, int coordenadas[2], int jugador)
{
    printf("Enviá la columna junto con la fila en la que vas a colocar el casillero ");
    if (direccion==TECLA0) printf("superior");
    else printf("izquierdo");
    printf(". Por ejemplo, enviar 47 significa columna 4 fila 7\n");
    RespuestaCoordenadas(barco, tablero, coordenadas, direccion, jugador);
}

void RespuestaCoordenadas(int barco, int tablero[JUGADORES][CASILLEROS][CASILLEROS], int coordenadas[2], char direccion, int jugador)
{
    bool coordenadasValidas;
    
    coordenadasValidas = ComprobarCoordenadas(barco, tablero, coordenadas, direccion, jugador);
    while (!(coordenadasValidas))
    {
        printf("Por favor, introducí una respuesta válida\n");
        coordenadasValidas = ComprobarCoordenadas(barco, tablero, coordenadas, direccion, jugador);
    }
}

bool ComprobarCoordenadas(int barco, int tablero[JUGADORES][CASILLEROS][CASILLEROS], int coordenadas[2], char direccion, int jugador)
{
    bool coordenadasValidas=true;
    int casillerosBarco = TamañoBarco(barco);
    
    scanf("%1i%1i", &coordenadas[0], &coordenadas[1]);
    LimpiarTeclado();
    if ((coordenadas[0]<0)||(coordenadas[1]<0)|| //Verifica coordenadas negativas
    ((direccion==TECLA0)&&((coordenadas[1]+casillerosBarco)>CASILLEROS))|| //Verifica que el barco entre verticalmente
    ((direccion==TECLA1)&&((coordenadas[0]+casillerosBarco)>CASILLEROS))) //Verifica que el barco entre horizontalmente
    coordenadasValidas=false;
    for (int i=0; ((i<casillerosBarco)&&(!coordenadasValidas)); i++)
    if (((direccion==TECLA0)&&(tablero[jugador][coordenadas[0]][coordenadas[1]+i]!=AGUA))|| //Verifica otros barcos verticalmente
    ((direccion==TECLA1)&&(tablero[jugador][coordenadas[0]+i][coordenadas[1]]!=AGUA))) //Verifica otros barcos horizontalmente
    coordenadasValidas=false;
    //Arreglar detección de otros barcos
    
    
    return coordenadasValidas;
}

void AgregarBarco(int barco, int jugador, int tablero[JUGADORES][CASILLEROS][CASILLEROS], int coordenadas[2], char direccion)
{
    int casillerosRestantesBarco = TamañoBarco(barco);
    while (casillerosRestantesBarco>0)
    {
        if (direccion==TECLA0) tablero[jugador][coordenadas[0]][coordenadas[1]+casillerosRestantesBarco-1]=barco;
        if (direccion==TECLA1) tablero[jugador][coordenadas[0]+casillerosRestantesBarco-1][coordenadas[1]]=barco;
        casillerosRestantesBarco--;
    }
}

void LimpiarTeclado() //Limpia el buffer del teclado
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
