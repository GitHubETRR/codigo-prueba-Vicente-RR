#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARACTERES_NOMBRE 30
#define MAX_CARACTERES_PRESENTACION 1000
#define CANTIDAD_ESTADISTICAS 5

#define MIN_AUMENTO_ESTADISTICAS -6
#define MAX_AUMENTO_ESTADISTICAS 6
#define ATAQUE 0
#define ATAQUE_ESPECIAL 1
#define DEFENSA 2
#define DEFENSA_ESPECIAL 3
#define VELOCIDAD 4

typedef struct {
	int potencia;
	int potenciaEspecial;

	float aumentoSalud;
	int aumentoEstadisticas[CANTIDAD_ESTADISTICAS];

	int usos;
} movimiento_t;


typedef struct {
	char nombre[MAX_CARACTERES_NOMBRE];
	char presentacion[MAX_CARACTERES_PRESENTACION];
	
	int salud;
	int saludMaxima;
	
	int ataque;
	int ataqueEspecial;
	int defensa;
	int defensaEspecial;
	int velocidad;
	int aumentoEstadisticas[CANTIDAD_ESTADISTICAS];
	
	movimiento_t ataque1;
	movimiento_t ataque2;
	movimiento_t ataque3;
	movimiento_t defensa1;
	movimiento_t defensa2;
	movimiento_t defensa3;
} personaje_t;

void Turno(personaje_t personajes[2], movimiento_t movimientos[2]);
int CompararVelocidades(personaje_t personajes[2]);
void Atacar(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);
void CalcularMultiplicadores(personaje_t personajes[2], float multiplicador[CANTIDAD_ESTADISTICAS-1], int personajeTurno);
void AumentarEstadisticas(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);
void AumentarSalud(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);

int main()
{
	return 0;
}

void Turno(personaje_t personajes[2], movimiento_t movimientos[2]) //Se almacena el nuevo estado de ambos personajes en un vector temporalmente para poder devolver ambos
{
    int personajeTurno=CompararVelocidades(personajes);
    
    for (int t=0; t<2; t++)
    {
        Atacar(personajes, personajeTurno, movimientos);
        AumentarEstadisticas(personajes, personajeTurno, movimientos);
        AumentarSalud(personajes, personajeTurno, movimientos);
        
        personajeTurno = (personajeTurno==0)?1:0;
        if (personajes[personajeTurno].salud==0) t=2; //Termina el turno
    }
}

int CompararVelocidades(personaje_t personajes[2])
{
    float velocidad[2];
    int personajeTurno;
    
    for (int personaje=0; personaje<2; personaje++)
    {
        if (personajes[personaje].aumentoEstadisticas[VELOCIDAD]<0)
            velocidad[personaje]=2.0/(2.0-(float)personajes[personaje].aumentoEstadisticas[VELOCIDAD]);
        else
            velocidad[personaje]=(2.0+(float)personajes[personaje].aumentoEstadisticas[VELOCIDAD])/2.0;
        
        velocidad[personaje]*=personajes[personaje].velocidad;
    }
    if (velocidad[0]==velocidad[1]) personajeTurno = rand()%2;
    else
        personajeTurno=(velocidad[0]>velocidad[1])?0:1;
    
    return personajeTurno;
}

void Atacar(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2])
{
    float multiplicador[CANTIDAD_ESTADISTICAS-1]; //Menos la velocidad, que ya fue calculada
    int personajeRival = (personajeTurno==0)?1:0;
    
    CalcularMultiplicadores(personajes, multiplicador, personajeTurno);
    
    personajes[personajeRival].salud-=multiplicador[ATAQUE]/multiplicador[DEFENSA]*movimientos[personajeTurno].potencia*personajes[personajeTurno].ataque/personajes[personajeRival].defensa;
    personajes[personajeRival].salud-=multiplicador[ATAQUE_ESPECIAL]/multiplicador[DEFENSA_ESPECIAL]*movimientos[personajeTurno].potenciaEspecial*personajes[personajeTurno].ataqueEspecial/personajes[personajeRival].defensaEspecial;
    if (personajes[personajeRival].salud<0) personajes[personajeRival].salud=0;
}

void CalcularMultiplicadores(personaje_t personajes[2], float multiplicador[CANTIDAD_ESTADISTICAS-1], int personajeTurno)
{
    int personajeRival = (personajeTurno==0)?1:0;
    
    multiplicador[ATAQUE]=(float) personajes[personajeTurno].aumentoEstadisticas[ATAQUE];
    multiplicador[ATAQUE_ESPECIAL]=(float) personajes[personajeTurno].aumentoEstadisticas[ATAQUE_ESPECIAL];
    multiplicador[DEFENSA]=(float) personajes[personajeRival].aumentoEstadisticas[DEFENSA];
    multiplicador[DEFENSA_ESPECIAL]=(float) personajes[personajeRival].aumentoEstadisticas[DEFENSA_ESPECIAL];
    for (int i=0; i<(CANTIDAD_ESTADISTICAS-1); i++)
    {
        if (multiplicador[i]<0)
            multiplicador[i]=2.0/(2.0-multiplicador[i]);
        else
            multiplicador[i]=(2.0+multiplicador[i])/2.0;
    }
}

void AumentarEstadisticas(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2])
{
    for (int i=0; i<CANTIDAD_ESTADISTICAS; i++)
    {
        personajes[personajeTurno].aumentoEstadisticas[i]+=movimientos[personajeTurno].aumentoEstadisticas[i];
        if (personajes[personajeTurno].aumentoEstadisticas[i]<MIN_AUMENTO_ESTADISTICAS)
            personajes[personajeTurno].aumentoEstadisticas[i]=MIN_AUMENTO_ESTADISTICAS;
        if (personajes[personajeTurno].aumentoEstadisticas[i]>MAX_AUMENTO_ESTADISTICAS)
            personajes[personajeTurno].aumentoEstadisticas[i]=MAX_AUMENTO_ESTADISTICAS;
    }
}

void AumentarSalud(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2])
{
    personajes[personajeTurno].salud+=personajes[personajeTurno].saludMaxima*movimientos[personajeTurno].aumentoSalud;
    if (personajes[personajeTurno].salud>personajes[personajeTurno].saludMaxima)
        personajes[personajeTurno].salud=personajes[personajeTurno].saludMaxima;
}
