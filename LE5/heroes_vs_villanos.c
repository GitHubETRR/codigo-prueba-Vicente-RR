#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CARACTERES_NOMBRE 30
#define MAX_CARACTERES_PRESENTACION 1000
#define CANTIDAD_ESTADISTICAS 5
#define CANTIDAD_MOVIMIENTOS 6

#define MIN_AUMENTO_ESTADISTICAS -6
#define MAX_AUMENTO_ESTADISTICAS 6
#define ATAQUE 0
#define ATAQUE_ESPECIAL 1
#define DEFENSA 2
#define DEFENSA_ESPECIAL 3
#define VELOCIDAD 4

typedef enum{
    INGRESAR=1,
    MOSTRAR,
    ELIMINAR,
    EDITAR,
    GUARDAR,
    SALIR
}opciones_t;

typedef struct {
    char nombre[MAX_CARACTERES_NOMBRE];

	int potencia;
	int potenciaEspecial;

	float aumentoSalud;
	int aumentoEstadisticas[CANTIDAD_ESTADISTICAS];

	int usos;
	int usosMaximos;
} movimiento_t;

typedef struct personaje{
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
	
	movimiento_t movimiento[CANTIDAD_MOVIMIENTOS];

    struct personaje * next;
} personaje_t;

personaje_t *_5TEL=NULL;

//MENÚ
void MostrarLista(void);
void ImprimirPersonaje(personaje_t * personaje);
void IngresarPersonaje(void);
void Menu(void);
void LiberarMemoria(void);
void LimpiarPantalla(void);

//JUEGO
void Turno(personaje_t personajes[2], movimiento_t movimientos[2]);
int CompararVelocidades(personaje_t personajes[2]);
void Atacar(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);
void CalcularMultiplicadores(personaje_t personajes[2], float multiplicador[CANTIDAD_ESTADISTICAS-1], int personajeTurno);
void AumentarEstadisticas(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);
void AumentarSalud(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);

int main (void){
    Menu();
    LiberarMemoria();
    return 0;
}

void Menu (void){
    opciones_t op;
    do{
        printf("Menu\n");
        printf("1_Ingresar un personaje\n");
        printf("2_Mostrar toda la lista\n");
        printf("3_Eliminar un personaje\n");
        printf("4_Editar un personaje\n");
        printf("5_Guardar los personajes\n");
        printf("6_Salir\n");
        scanf("%d", &op);
        switch (op){
            case INGRESAR:
                 IngresarPersonaje();
                break;
            case MOSTRAR:
                 MostrarLista();
                break;
            case ELIMINAR:

                break;
            case EDITAR:
                break;
            case GUARDAR:
                break;

        }   
    }while(op!=SALIR);
}

void ImprimirPersonaje(personaje_t * personaje){
    printf("\n--------------------\n");
    printf("Nombre: %s\n",personaje->nombre);
    printf("Presentación: %s\n",personaje->presentacion);
    printf("\nESTADÍSTICAS:\n");
    printf("Salud: %i\n",personaje->saludMaxima);
    printf("Ataque: %i\n",personaje->ataque);
    printf("Ataque Especial: %i\n",personaje->ataqueEspecial);
    printf("Defensa: %i\n",personaje->defensa);
    printf("Defensa Especial: %i\n",personaje->defensaEspecial);
    printf("Velocidad: %i\n",personaje->velocidad);
    for (int i=0; i<CANTIDAD_MOVIMIENTOS; i++)
    {
        printf("-\n");
        printf("Movimiento %i: %s\n", (i+1), personaje->movimiento[i].nombre);
        printf("Potencia / Potencia Especial: %i / %i\n", personaje->movimiento[i].potencia, personaje->movimiento[i].potenciaEspecial);
        printf("Aumento de SALUD / ATAQUE / ATAQUE ESPECIAL / DEFENSA / DEFENSA ESPECIAL / VELOCIDAD: %.2f / %i / %i / %i / %i / %i\n", personaje->movimiento[i].aumentoSalud, personaje->movimiento[i].aumentoEstadisticas[ATAQUE], personaje->movimiento[i].aumentoEstadisticas[ATAQUE_ESPECIAL], personaje->movimiento[i].aumentoEstadisticas[DEFENSA], personaje->movimiento[i].aumentoEstadisticas[DEFENSA_ESPECIAL], personaje->movimiento[i].aumentoEstadisticas[VELOCIDAD]);
        printf("Usos: %i\n", personaje->movimiento[i].usosMaximos);
    }
    printf("--------------------\n");
}

void IngresarPersonaje(void){
    personaje_t * personaje_ptr= (personaje_t *)malloc(sizeof(personaje_t));
    if(personaje_ptr==NULL){
        printf("Out of Memory");
        exit(1);
    }

    printf("Nombre: ");
    scanf("%s",personaje_ptr->nombre);
    printf("Presentación: ");
    scanf("%s",personaje_ptr->presentacion);
    printf("Salud máxima: ");
    scanf("%i",&personaje_ptr->saludMaxima);
    printf("Ataque: ");
    scanf("%i",&personaje_ptr->ataque);
    printf("Ataque especial: ");
    scanf("%i",&personaje_ptr->ataqueEspecial);
    printf("Defensa: ");
    scanf("%i",&personaje_ptr->defensa);
    printf("Defensa especial: ");
    scanf("%i",&personaje_ptr->defensaEspecial);
    printf("Velocidad: ");
    scanf("%i",&personaje_ptr->velocidad);
    for (int i=0; i<CANTIDAD_MOVIMIENTOS; i++)
    {
        printf("-\n");
        printf("MOVIMIENTO %i: %s\n", (i+1), personaje_ptr->movimiento[i].nombre);
        printf("Nombre: ");
        scanf("%s",personaje_ptr->movimiento[i].nombre);
        printf("Potencia: ");
        scanf("%i",&personaje_ptr->movimiento[i].potencia);
        printf("Potencia especial: ");
        scanf("%i",&personaje_ptr->movimiento[i].potenciaEspecial);
        printf("Aumento de salud: ");
        scanf("%f",&personaje_ptr->movimiento[i].aumentoSalud);
        printf("Aumento de ataque: ");
        scanf("%i",&personaje_ptr->movimiento[i].aumentoEstadisticas[ATAQUE]);
        printf("Aumento de ataque especial: ");
        scanf("%i",&personaje_ptr->movimiento[i].aumentoEstadisticas[ATAQUE_ESPECIAL]);
        printf("Aumento de defensa: ");
        scanf("%i",&personaje_ptr->movimiento[i].aumentoEstadisticas[DEFENSA]);
        printf("Aumento de defensa especial: ");
        scanf("%i",&personaje_ptr->movimiento[i].aumentoEstadisticas[DEFENSA_ESPECIAL]);
        printf("Aumento de velocidad: ");
        scanf("%i",&personaje_ptr->movimiento[i].aumentoEstadisticas[VELOCIDAD]);
        printf("Usos: ");
        scanf("%i",&personaje_ptr->movimiento[i].usosMaximos);
    }

    personaje_ptr->next=NULL;
    printf("\n");
    if(_5TEL==NULL){
        _5TEL=personaje_ptr;
    }
    else{
        personaje_ptr->next=_5TEL;
        _5TEL=personaje_ptr;
    }

}

void MostrarLista(void){
    personaje_t * lista_personajes=_5TEL;
    while(lista_personajes!=NULL){
        ImprimirPersonaje(lista_personajes);
        lista_personajes=lista_personajes->next;
    }
}

void LiberarMemoria(void){
    personaje_t * lista_personajes=_5TEL;

    while(_5TEL!=NULL){
        free(lista_personajes);
        _5TEL=_5TEL->next;
        lista_personajes=_5TEL;
    }
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
