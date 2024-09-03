#include <stdio.h>
#include <stdlib.h>
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
#define DIRECCION_VERTICAL 1
#define DIRECCION_HORIZONTAL 2
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

int JugarPartida(int[JUGADORES][CASILLEROS][CASILLEROS]);
void VaciarTablero(int[JUGADORES][CASILLEROS][CASILLEROS]);
void ImprimirTablero(int[JUGADORES][CASILLEROS][CASILLEROS], int, bool);

void ArmarTablero(int[JUGADORES][CASILLEROS][CASILLEROS]);
char PedirDireccion(int);
char Respuesta(void);
void PedirCoordenadas(int barco, int [JUGADORES][CASILLEROS][CASILLEROS], char, int[2], int);
int TamañoBarco(int);
void RespuestaCoordenadas(int, int [JUGADORES][CASILLEROS][CASILLEROS], int[2], char, int);
bool ComprobarCoordenadas(int, int [JUGADORES][CASILLEROS][CASILLEROS], int[2], char, int);
void AgregarBarco(int, int, int[JUGADORES][CASILLEROS][CASILLEROS], int[2], char);

void Atacar(int, int[JUGADORES][CASILLEROS][CASILLEROS]);
bool ComprobarCoordenadasAtaque(int, int[2], int[JUGADORES][CASILLEROS][CASILLEROS]);
void VerificarBarcoDerribado(int, int[2], int[JUGADORES][CASILLEROS][CASILLEROS]);
void DerribarBarco(int, int, int[JUGADORES][CASILLEROS][CASILLEROS]);
void TerminarTurno(int, int[2], int[JUGADORES][CASILLEROS][CASILLEROS]);
int VerificarGanador(int[JUGADORES][CASILLEROS][CASILLEROS]);
bool TableroVacio(int, int[JUGADORES][CASILLEROS][CASILLEROS]);
bool AnunciarGanador(int);

void LimpiarTeclado(void);
void LimpiarPantalla(void);

int main()
{
    int tablero[JUGADORES][CASILLEROS][CASILLEROS];
    int ganador;
    int victoriasJugador0=0;
    int victoriasJugador1=0;
    
    do
    {
        ganador = JugarPartida(tablero);
        if ((ganador==0)||(ganador==(0-2))) victoriasJugador0++;
        if ((ganador==1)||(ganador==(1-2))) victoriasJugador1++;
        printf("Victorias del JUGADOR 0: %i\n", victoriasJugador0);
        printf("Victorias del JUGADOR 1: %i\n", victoriasJugador1);
        getchar();
        LimpiarTeclado();
    } while (ganador>=0);
    
    return 0;
}

int JugarPartida(int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    bool jugarDeNuevo;
    int ganador = -1; //Ningún jugador
    int turno = 0;
    
    VaciarTablero(tablero);
    ArmarTablero(tablero);
    do
    {
        Atacar(turno, tablero);
        ganador = VerificarGanador(tablero);
        turno = (turno==0)?1:0; //Cambio de turno
    } while (ganador==-1);
    jugarDeNuevo = AnunciarGanador(ganador);
    if (!(jugarDeNuevo))
    ganador-=2; //De este modo, se envía un número negativo, indicando que el usuario no quiere jugar más
    
    return ganador;
}

bool AnunciarGanador(int ganador)
{
    char respuesta;
    bool jugarDeNuevo;
    
    printf("GANADOR: JUGADOR %i\n", ganador);
    printf("Enviá %c para jugar de nuevo", TECLA0);
    scanf("%c", &respuesta);
    LimpiarTeclado();
    jugarDeNuevo = (respuesta==TECLA0)?true:false;
    
    return jugarDeNuevo;
}

void Atacar(int atacante, int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    int coordenadas[2];
    int atacado = (atacante==0)?1:0; //Operador ternario, hace que el atacado sea el contrario al atacante
    bool coordenadasValidas;
    
    LimpiarPantalla();
    ImprimirTablero(tablero, atacado, false);
    
    printf("JUGADOR %i\n", atacante);
    printf("Enviá la columna junto con la fila en la que vas a disparar\n");
    coordenadasValidas = ComprobarCoordenadasAtaque(atacante, coordenadas, tablero);
    while (!(coordenadasValidas))
    {
        printf("Por favor, introducí una respuesta válida\n");
        coordenadasValidas = ComprobarCoordenadasAtaque(atacado, coordenadas, tablero);
    }
    TerminarTurno(atacado, coordenadas, tablero);
}

void TerminarTurno(int atacado, int coordenadas[2], int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    int barcoDerribado;
    
    LimpiarPantalla();
    VerificarBarcoDerribado(atacado, coordenadas, tablero);
    ImprimirTablero(tablero, atacado, false);
    printf("Presioná enter para terminar el turno");
    getchar();
    LimpiarTeclado();
}

void VerificarBarcoDerribado(int atacado, int coordenadas[2], int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    int barcoDerribado = tablero[atacado][coordenadas[0]][coordenadas[1]];
    
    tablero[atacado][coordenadas[0]][coordenadas[1]]+=DISPARO;
    if (barcoDerribado!=AGUA)
    {
        for (int columna; columna<CASILLEROS; columna++)
        {
            for (int fila; fila<CASILLEROS; fila++)
            {
                if (tablero[atacado][columna][fila]==barcoDerribado) barcoDerribado=0; //Quedan partes del barco por disparar
            }
        }
    }
    if (barcoDerribado) DerribarBarco(barcoDerribado, atacado, tablero);
}

void DerribarBarco(int barcoDerribado, int atacado, int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    int direccion=0; //0 = no definida
    
    for (int columna; columna<CASILLEROS; columna++)
    {
        for (int fila; fila<CASILLEROS; fila++)
        {
            if (tablero[atacado][columna][fila]==(barcoDerribado+DISPARO))
            {
                if (direccion==0) //Si la dirección aun no está definida, la calcula
                {
                    if (tablero[atacado][columna+1][fila]==(barcoDerribado+DISPARO)) direccion=DIRECCION_HORIZONTAL;
                    else direccion = DIRECCION_VERTICAL;
                }
                if (direccion==DIRECCION_VERTICAL) tablero[atacado][columna][fila]=BAJADO_VERTICAL;
                else tablero[atacado][columna][fila]=BAJADO_HORIZONTAL;
            }
        }
    }
}

bool ComprobarCoordenadasAtaque(int atacado, int coordenadas[2], int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    bool coordenadasValidas;
    
    scanf("%1i%1i", &coordenadas[0], &coordenadas[1]);
    LimpiarTeclado();
    if (tablero[atacado][coordenadas[0]][coordenadas[1]]<DISPARO) coordenadasValidas=true;
    else coordenadasValidas=false;
    
    return coordenadasValidas;
}

int VerificarGanador(int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    int jugadorGanador = -1;
    
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        bool ganador = TableroVacio(jugador, tablero);
        
        if (ganador) jugadorGanador=jugador;
    }
    
    return jugadorGanador;
}

bool TableroVacio(int jugador, int tablero[JUGADORES][CASILLEROS][CASILLEROS])
{
    bool vacio = true;
    
    for (int columna=0; columna<CASILLEROS; columna++)
    {
        for (int fila=0; fila<CASILLEROS; fila++)
        if ((tablero[jugador][columna][fila]!=AGUA)&&(tablero[jugador][columna][fila]<DISPARO)) //Verifica si el tablero tiene un barco no disparado
        vacio = false;
    }
    
    return vacio;
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
            char caracterCasillero=' ';
            
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
        for (int barco=1; barco<(CANTIDAD_DE_BARCOS+1); barco++)
        {
            char direccion;
            int coordenadas[2];
            
            LimpiarPantalla();
            printf("JUGADOR %i\n", jugador);
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
    const char nombreBarco[CANTIDAD_DE_BARCOS][CARACTERES_NOMBRES_BARCOS] = {"PORTAVIONES","DESTRUCTOR A","DESTRUCTOR B","PATRULLERO A","PATRULLERO B"};
    
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
    for (int i=0; (i<casillerosBarco); i++)
    if (((direccion==TECLA0)&&(tablero[jugador][coordenadas[0]][coordenadas[1]+i]!=AGUA))|| //Verifica otros barcos verticalmente
    ((direccion==TECLA1)&&(tablero[jugador][coordenadas[0]+i][coordenadas[1]]!=AGUA))) //Verifica otros barcos horizontalmente
    coordenadasValidas=false;
    
    
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

void LimpiarPantalla()
{
    // Detectar el sistema operativo
    #ifdef _WIN32
        system("cls"); // Limpiar pantalla en Windows
    #else
        system("clear"); // Limpiar pantalla en Unix/Linux
    #endif
}
