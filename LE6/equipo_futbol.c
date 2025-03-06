#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define CANTIDAD_JUGADORES 22
#define MAX_CHAR 50
#define MIN_CAMISETA 1
#define MAX_CAMISETA 99
#define MAX_TITULARES 11
#define MAX_SUPLENTES 11
#define TECLA_TITULAR 'T'
#define DISPONIBLE 0
#define DISPONIBLE_TITULAR 1
#define DISPONIBLE_SUPLENTE 2

typedef struct
{
    char nombre[MAX_CHAR];
    int camiseta;
    bool titular;
} jugador_t;

int main()
{
    jugador_t equipo[CANTIDAD_JUGADORES];
    
    ArmarEquipo(equipo);
    
    return 0;
}

void ArmarEquipo(jugador_t equipo[CANTIDAD_JUGADORES])
{
    for (int jugador=0; jugador<CANTIDAD_JUGADORES; jugador++)
        PedirDatos(equipo, jugador);
}

void PedirDatos(jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    PedirNombre(equipo, jugador);
    PedirCamiseta(equipo, jugador);
    PedirTitular(equipo, jugador);
}

void PedirNombre(jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    printf("Introducí el nombre del %i° jugador del equipo\n", jugador);
    scanf("%s", equipo[jugador].nombre);
}

void PedirCamiseta(jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    do
    {
        bool valido;
        int numero;
        
        printf("Introducí el número de camiseta\n");
        scanf("%i", &numero);
        valido = ComprobarCamiseta(numero, equipo, jugador);
        if (!valido)
            printf("Número no válido\n");
    } while (!valido);
}

bool ComprobarCamiseta(int numero, jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    bool valido=true;
    
    if ((numero<MIN_CAMISETA)||(numero>MAX_CAMISETA)) //Calcula si está fuera de los límites
        valido=false;
    else
        valido = CamisetaUsada(numero, equipo, jugador); //Calcula si el número ya está ocupado
    
    return valido;
}

bool CamisetaUsada(int numero, jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    bool valido=true;
    
    for (int i=0; i<jugador; i++)
        if (equipo[i].camiseta==numero)
            valido=false;
    
    return valido;
}

void PedirTitular(jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    char tecla;
    int lugarDisponible = ComprobarLugar(equipo, jugador);
    
    switch (lugarDisponible)
    {
        case DISPONIBLE:
            printf("Enviá %c si el jugador es titular (si es suplente, otro caracter\n", TECLA_TITULAR);
            scanf("%c", &tecla);
            if (tecla==TECLA_TITULAR)
                equipo[jugador].titular = true;
            else
                equipo[jugador].titular = false;
            break;
        
        case DISPONIBLE_TITULAR:
            equipo[jugador].titular = true;
            break;
        
        case DISPONIBLE_SUPLENTE:
            equipo[jugador].titular = false;
            break;
    }
}

int ComprobarLugar(jugador_t equipo[CANTIDAD_JUGADORES], int jugador)
{
    int lugarDisponible = DISPONIBLE;
    int titulares = 0;
    int suplentes = 0;
    
    for (int i=0; i<jugador, i++)
        if (equipo[i].titular)
            titulares++;
        else
            suplentes++;
    if (titulares>=MAX_TITULARES)
        lugarDisponible=DISPONIBLE_SUPLENTE;
    if (suplentes>=MAX_SUPLENTES)
        lugarDisponible=DISPONIBLE_TITULAR;
    
    return lugarDisponible;
}
