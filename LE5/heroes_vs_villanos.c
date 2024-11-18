/*
FUNCIONES RESTANTES:
Que obligue al jugador a cambiar de personaje cuando es debilitado
Verificación de victoria
Interfaz
Mensajes
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_CARACTERES_NOMBRE 50
#define MAX_CARACTERES_PRESENTACION 1000
#define CANTIDAD_ESTADISTICAS 5
#define CANTIDAD_MOVIMIENTOS 6

#define SIN_PERSONAJE 0
#define SIN_CAMBIO -1
#define JUGADORES 2
#define MAX_PERSONAJES 6
#define MIN_AUMENTO_ESTADISTICAS -6
#define MAX_AUMENTO_ESTADISTICAS 6
#define ATAQUE 0
#define ATAQUE_ESPECIAL 1
#define DEFENSA 2
#define DEFENSA_ESPECIAL 3
#define VELOCIDAD 4

#define FORCEJEO -1
#define CAMBIO -2
#define FORCEJEO_POTENCIA 20
#define FORCEJEO_PERDIDA_SALUD 0.25

typedef enum {
    JUGAR=1,
    INGRESAR,
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

typedef struct personaje {
    int id;
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

personaje_t *lista_personajes=NULL;

//MENÚ
void LeerDatos(void);
void Menu(void);
void OrdenarID(void);
void PedirDatos(personaje_t * personaje_ptr);
void IngresarPersonaje(void);
void ImprimirPersonaje(personaje_t * personaje, bool mostrarDatos);
void MostrarLista(bool mostrarDatos);
personaje_t * ApuntarID(int id);
void BuscarPersonaje(bool eliminar);
void Eliminar(personaje_t * personaje);
void GuardarDatos(void);
void LiberarMemoria(void);
void LimpiarTeclado(void);
void LimpiarPantalla(void);

//JUEGO
void Jugar(void);
void ElegirPersonajes(personaje_t personajes[JUGADORES][MAX_PERSONAJES]);
void VaciarEstadisticas(personaje_t personajes[JUGADORES][MAX_PERSONAJES]);
int MenuMovimientos(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int jugador, bool usosDisponibles);
void ElegirOpcion(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int movimientos[JUGADORES], int cambioPersonaje[JUGADORES], int jugador, int opcion, bool usosDisponibles);
void ElegirMovimientos(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int movimientos[JUGADORES], int cambioPersonaje[JUGADORES]);
bool VerificarUsos(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int jugador, int personajesJugando[JUGADORES]);
void CambiarPersonajes(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int cambioPersonaje[JUGADORES], int personajesJugando[JUGADORES]);
void Turno(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int movimientos[JUGADORES]);
int CompararVelocidades(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES]);
void Atacar(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int personajeTurno, int movimientos[JUGADORES]);
void CalcularMultiplicadores(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], float multiplicador[CANTIDAD_ESTADISTICAS-1], int personajeTurno);
void AumentarEstadisticas(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int personajeTurno, int movimientos[JUGADORES]);
void AumentarSalud(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int personajeTurno, int movimientos[JUGADORES]);

int main(void)
{
    LeerDatos();
    Menu();
    LiberarMemoria();
    return 0;
}

void LeerDatos(void)
{
    FILE *fp = fopen("lista.bin", "rb"); //fp=file pointer
    if (fp == NULL) {
        printf("El archivo de lista no existe, creando uno nuevo...\n");
        fp = fopen("lista.bin", "wb+");  // Crear el archivo si no existe
        if (fp == NULL)
        {
            printf("Error: No se pudo crear el archivo.\n");
            exit(1);
        }
    }

    bool salir=false;
    do{
        personaje_t * personaje_ptr= (personaje_t *)malloc(sizeof(personaje_t)); //personaje_ptr apunta a uno nuevo creado con malloc
        if(fread(personaje_ptr, sizeof(personaje_t), 1, fp)==1){ //fread guarda en la memoria de personaje_ptr los datos del personaje guardado, y en caso de que existan dichos datos...
            if(lista_personajes==NULL){ //Si es el primer personaje guardado de la lista, se indica al apuntado por personaje_ptr como el primero
                lista_personajes=personaje_ptr;
                lista_personajes->next=NULL;
            
            }
            else //Si ya existen otros personajes en la lista...
            {
                personaje_t * lista = lista_personajes; //Crea otro puntero temporal para no perder el valor guardado en el global
                while(lista->next!=NULL){ //Recorre toda la lista, hasta que el puntero lista apunte al último personaje
                    lista=lista->next;
                }
                lista->next=personaje_ptr; //Hace que el último personaje de la lista tenga al nuevo como siguiente, convirtiendo al nuevo en el último de la lista
                personaje_ptr->next=NULL; //Finalmente, el nuevo personaje tiene a NULL como siguiente, por lo que es el último
            }
        }else{ //En caso de que no existan datos de otro personaje, se libera de la memoria dinámica
            free(personaje_ptr);
            salir=true;
        }
    }while(!salir);
    fclose(fp);
    OrdenarID();
}

void Menu(void)
{
    opciones_t op;
    do
    {
        printf("Menu\n");
        printf("1_Jugar\n");
        printf("2_Ingresar un personaje\n");
        printf("3_Mostrar toda la lista\n");
        printf("4_Eliminar un personaje\n");
        printf("5_Editar un personaje\n");
        printf("6_Guardar los personajes\n");
        printf("7_Salir\n");
        scanf("%d", &op);
        LimpiarTeclado();
        LimpiarPantalla();
        switch (op)
        {
            case JUGAR:
                if (lista_personajes==NULL)
                {
                    printf("No hay personajes en el sistema\n");
                }
                else
                {
                    Jugar();
                }
                break;
            case INGRESAR:
                 IngresarPersonaje();
                break;
            case MOSTRAR:
                 MostrarLista(true);
                break;
            case ELIMINAR:
                BuscarPersonaje(true);
                break;
            case EDITAR:
                BuscarPersonaje(false);
                break;
            case GUARDAR:
                GuardarDatos();
                break;
        }
        printf("Presione enter para continuar\n");
        fflush(stdin);
        getchar();
        LimpiarTeclado();
        LimpiarPantalla();
    }while(op!=SALIR);
}

void OrdenarID(void)
{
    personaje_t * lista=lista_personajes;
    for (int id=1; lista!=NULL; id++)
    {
        lista->id=id;
        lista=lista->next;
    }
}

void PedirDatos(personaje_t * personaje_ptr)
{
    printf("Nombre: ");
    //scanf("%s",personaje_ptr->nombre);
    fgets(personaje_ptr->nombre, sizeof(personaje_ptr->nombre), stdin); //fgets permite incluir espacios
    printf("Presentación: ");
    //scanf("%s",personaje_ptr->presentacion);
    fgets(personaje_ptr->presentacion, sizeof(personaje_ptr->presentacion), stdin);
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
    LimpiarTeclado();
    for (int i=0; i<CANTIDAD_MOVIMIENTOS; i++)
    {
        printf("-\n");
        printf("MOVIMIENTO %i:\n", (i+1));
        printf("Nombre: ");
        //scanf("%s",personaje_ptr->movimiento[i].nombre);
        fgets(personaje_ptr->movimiento[i].nombre, sizeof(personaje_ptr->movimiento[i].nombre), stdin);
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
        LimpiarTeclado();
    }
}

void IngresarPersonaje(void) //Considerando que el usuario conoce todas las limitaciones
{
    personaje_t * personaje_ptr = (personaje_t *)malloc(sizeof(personaje_t));
    if(personaje_ptr==NULL)
    {
        printf("Out of Memory");
        exit(1);
    }

    PedirDatos(personaje_ptr);

    printf("\n");
    //Coloca al nuevo personaje al final de la fila
    personaje_ptr->next=NULL;
    if(lista_personajes==NULL)
    {
        lista_personajes=personaje_ptr;
    }
    else
    {
        personaje_t * lista=lista_personajes;
        while (lista->next!=NULL)
            lista=lista->next;
        lista->next=personaje_ptr;
    }
    OrdenarID();
}

void ImprimirPersonaje(personaje_t * personaje, bool mostrarDatos)
{
    printf("\n--------------------\n");
    printf("ID: %i\n",personaje->id);
    printf("Nombre: %s\n",personaje->nombre);
    if (mostrarDatos)
    {
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
    }
    printf("--------------------\n");
}

void MostrarLista(bool mostrarDatos)
{
    personaje_t * lista=lista_personajes;
    while(lista!=NULL)
    {
        ImprimirPersonaje(lista, mostrarDatos);
        lista=lista->next;
    }
}

personaje_t * ApuntarID(int id)
{
    personaje_t * lista=lista_personajes;
    while ((lista!=NULL)&&(lista->id!=id))
        lista=lista->next;
    
    return lista;
}

void BuscarPersonaje(bool eliminar)
{
    int id;
    char opcion;
    personaje_t * personaje_ptr;

    printf("ID: ");
    scanf("%i", &id);
    LimpiarTeclado();
    personaje_ptr = ApuntarID(id);
    if (personaje_ptr==NULL)
        printf("No se encontró el personaje\n");
    else
    {
        if (eliminar)
            printf("Eliminar a ");
        else
            printf("Editar a ");
        printf("%s(S/N)", personaje_ptr->nombre);
        scanf("%c", &opcion);
        LimpiarTeclado();
        if ((opcion=='S')||(opcion=='s'))
        {
            if (eliminar)
                Eliminar(personaje_ptr);
            else
                PedirDatos(personaje_ptr);
        }
    }
}

void Eliminar(personaje_t * personaje)
{
    if (personaje==lista_personajes)
        lista_personajes=lista_personajes->next;
    else
    {
        personaje_t * lista=lista_personajes;
        while (lista->next!=personaje)
        {
            lista=lista->next;
            if (lista->next==NULL)
            {
                printf("Error: No se encontró al personaje en la lista");
                exit(1);
            }
        }
        lista->next=(lista->next)->next;
    }
    printf("Personaje eliminado exitosamente\n");
    free(personaje);
    OrdenarID();
}

void GuardarDatos(void)
{
    FILE * fp= fopen ("lista.bin", "wb");
    personaje_t * lista=lista_personajes;
    while(lista!=NULL){
        fwrite((personaje_t *)lista, sizeof(personaje_t), 1, fp);
        lista=lista->next;
    }
    fclose(fp);
    printf("Datos guardados\n");
}

void LiberarMemoria(void)
{
    personaje_t * lista=lista_personajes;

    while(lista!=NULL)
    {
        lista=lista_personajes->next; //lista apunta al next del que se guarda en lista_personajes, de modo que no se pierda
        free(lista_personajes);
        lista_personajes=lista;
    }
}

void LimpiarTeclado()
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

void Jugar(void)
{
    bool jugar=true;
    personaje_t personajes[JUGADORES][MAX_PERSONAJES];
    int movimientos[JUGADORES];
    int personajesJugando[JUGADORES];
    int cambioPersonaje[JUGADORES];

    ElegirPersonajes(personajes);
    VaciarEstadisticas(personajes);
    do
    {
        ElegirMovimientos(personajes, personajesJugando, movimientos, cambioPersonaje);
        CambiarPersonajes(personajes, cambioPersonaje, personajesJugando);
        Turno(personajes, personajesJugando, movimientos);
    } while (jugar);
    
}

void ElegirPersonajes(personaje_t personajes[JUGADORES][MAX_PERSONAJES])
{
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        MostrarLista(false);
        for (int personaje=0; personaje<MAX_PERSONAJES; personaje++)
        {
            int id;
            bool respuestaValida;
            do
            {
                respuestaValida = true;
                printf("Jugador %i, introducí el ID del %i° personaje\n", (jugador+1), (personaje+1));
                if (personaje!=0) //Si no es el primer personaje, porque el equipo no puede estar vacío
                    printf("Enviá %i para terminar el equipo\n", SIN_PERSONAJE);
                scanf("%i", &id);
                if ((id==SIN_PERSONAJE)&&(personaje!=0))
                {
                    while (personaje<MAX_PERSONAJES)
                    {
                        personajes[jugador][personaje].id=SIN_PERSONAJE;
                        personaje++;
                    }
                }
                else
                {
                    if (ApuntarID(id)!=NULL)
                        personajes[jugador][personaje] = *ApuntarID(id);
                    else
                    {
                        respuestaValida=false;
                        printf("No se encontró el personaje\n");
                    }
                }
            } while (!respuestaValida);
        }
        LimpiarPantalla();
    }
}

void VaciarEstadisticas(personaje_t personajes[JUGADORES][MAX_PERSONAJES])
{
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        for (int personaje=0; personaje<MAX_PERSONAJES; personaje++)
        {
            personajes[jugador][personaje].salud = personajes[jugador][personaje].saludMaxima;
            for (int estadistica=0; estadistica<CANTIDAD_ESTADISTICAS; estadistica++)
            {
                personajes[jugador][personaje].aumentoEstadisticas[estadistica] = 0;
            }
            for (int movimiento=0; movimiento<CANTIDAD_MOVIMIENTOS; movimiento++)
            {
                personajes[jugador][personaje].movimiento[movimiento].usos = personajes[jugador][personaje].movimiento[movimiento].usosMaximos;
            }
        }
    }
}

int MenuMovimientos(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int jugador, bool usosDisponibles)
{
    int opcion=1;

    printf("Jugador %i\n", jugador);
    for (int movimiento=0; movimiento<CANTIDAD_MOVIMIENTOS; movimiento++)
    {
        printf("%i_%s - %i/%i\n", opcion, personajes[jugador][personajesJugando[jugador]].movimiento[movimiento].nombre, personajes[jugador][personajesJugando[jugador]].movimiento[movimiento].usos, personajes[jugador][personajesJugando[jugador]].movimiento[movimiento].usosMaximos);
        opcion++;
    }
    for (int personaje=0; personaje<MAX_PERSONAJES; personaje++)
    {
        if (personajes[jugador][personaje].id!=SIN_PERSONAJE)
        {
            if (personaje!=personajesJugando[jugador])
                printf("%i_%s - %i%\n", opcion, personajes[jugador][personaje].nombre, (100*personajes[jugador][personaje].salud/personajes[jugador][personaje].saludMaxima));
            opcion++;
        }
    }
    if (!usosDisponibles)
        printf("%i_Forcejeo\n", opcion);
    return opcion;
}

void ElegirOpcion(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int movimientos[JUGADORES], int cambioPersonaje[JUGADORES], int jugador, int opcion, bool usosDisponibles)
{
    int eleccion;
    bool opcionValida=false;

    do
    {
        scanf("%i", &eleccion);
        if ((eleccion==opcion)&&(!usosDisponibles))
        {
            movimientos[jugador]=FORCEJEO;
            opcionValida=true;
        }
        else
        {
            if ((eleccion>0)&&(eleccion<opcion)&&((eleccion-CANTIDAD_MOVIMIENTOS-1)!=personajesJugando[jugador])) //Se encuentra en el rango de opciones
            {
                if (eleccion<=CANTIDAD_MOVIMIENTOS) //se eligió un movimiento
                {
                    if (personajes[jugador][personajesJugando[jugador]].movimiento[(eleccion-1)].usos > 0)
                    {
                        movimientos[jugador]=eleccion-1;
                        personajes[jugador][personajesJugando[jugador]].movimiento[movimientos[jugador]].usos--;
                        opcionValida=true;
                    }
                    else
                        printf("No te quedan usos para este movimiento\n");
                }
                else //se eligió un personaje
                {
                    if (personajes[jugador][eleccion-CANTIDAD_MOVIMIENTOS-1].salud>0)
                    {
                        cambioPersonaje[jugador]=eleccion-CANTIDAD_MOVIMIENTOS-1;
                        movimientos[jugador]=CAMBIO;
                        opcionValida=true;
                    }
                    else
                        printf("%s está debilitado\n", personajes[jugador][eleccion-CANTIDAD_MOVIMIENTOS-1].nombre);
                }
            }
            else
                printf("Introducí una opción válida\n");
        }
    } while (!opcionValida);
}

void ElegirMovimientos(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int movimientos[JUGADORES], int cambioPersonaje[JUGADORES])
{
    int opcion;
    bool usosDisponibles; //Si quedan usos disponibles para cualquier movimiento

    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        cambioPersonaje[jugador] = SIN_CAMBIO;
        usosDisponibles = VerificarUsos(personajes, jugador, personajesJugando);
        opcion = MenuMovimientos(personajes, personajesJugando, jugador, usosDisponibles);

        ElegirOpcion(personajes, personajesJugando, movimientos, cambioPersonaje, jugador, opcion, usosDisponibles);
        
        LimpiarPantalla();
    }
}

bool VerificarUsos(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int jugador, int personajesJugando[JUGADORES])
{
    bool usosDisponibles=false;
    for (int i=0; i<CANTIDAD_MOVIMIENTOS; i++)
    {
        if (personajes[jugador][personajesJugando[jugador]].movimiento[i].usos>0)
            usosDisponibles=true;
    }
    
    return usosDisponibles;
}

void CambiarPersonajes(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int cambioPersonaje[JUGADORES], int personajesJugando[JUGADORES])
{
    for (int jugador=0; jugador<JUGADORES; jugador++)
    {
        if (cambioPersonaje[jugador]!=SIN_CAMBIO)
        {
            personajesJugando[jugador] = cambioPersonaje[jugador];
        }
    }
}


void Turno(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int movimientos[JUGADORES]) //Se almacena el nuevo estado de ambos personajes en un vector temporalmente para poder devolver ambos
{
    int personajeTurno=CompararVelocidades(personajes, personajesJugando);
    
    for (int t=0; t<JUGADORES; t++)
    {
        if (movimientos[personajeTurno]!=CAMBIO)
        {
            Atacar(personajes, personajesJugando, personajeTurno, movimientos);
            if (movimientos[personajeTurno]==FORCEJEO)
            {
                personajes[personajeTurno][personajesJugando[personajeTurno]].salud -= personajes[personajeTurno][personajesJugando[personajeTurno]].saludMaxima * FORCEJEO_PERDIDA_SALUD;
                if (personajes[personajeTurno][personajesJugando[personajeTurno]].salud<0)
                    personajes[personajeTurno][personajesJugando[personajeTurno]].salud=0;
            }
            else
            {
                AumentarEstadisticas(personajes, personajesJugando, personajeTurno, movimientos);
                AumentarSalud(personajes, personajesJugando, personajeTurno, movimientos);
            }
        }
        
        personajeTurno = (personajeTurno==0)?1:0;
        if (personajes[personajeTurno][personajesJugando[personajeTurno]].salud==0) t=JUGADORES; //Termina el turno
    }
}

int CompararVelocidades(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES])
{
    float velocidad[JUGADORES];
    int personajeTurno;
    
    for (int personaje=0; personaje<JUGADORES; personaje++)
    {
        if (personajes[personaje][personajesJugando[personaje]].aumentoEstadisticas[VELOCIDAD]<0)
            velocidad[personaje]=2.0/(2.0-(float)personajes[personaje][personajesJugando[personaje]].aumentoEstadisticas[VELOCIDAD]);
        else
            velocidad[personaje]=(2.0+(float)personajes[personaje][personajesJugando[personaje]].aumentoEstadisticas[VELOCIDAD])/2.0;
        
        velocidad[personaje]*=personajes[personaje][personajesJugando[personaje]].velocidad;
    }
    if (velocidad[0]==velocidad[1]) personajeTurno = rand()%JUGADORES;
    else
        personajeTurno=(velocidad[0]>velocidad[1])?0:1;
    
    return personajeTurno;
}

void Atacar(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int personajeTurno, int movimientos[JUGADORES])
{
    float multiplicador[CANTIDAD_ESTADISTICAS-1]; //Menos la velocidad, que ya fue calculada
    int personajeRival = (personajeTurno==0)?1:0;
    
    CalcularMultiplicadores(personajes, personajesJugando, multiplicador, personajeTurno);
    if (movimientos[personajeTurno]==FORCEJEO)
    {
        personajes[personajeRival][personajesJugando[personajeRival]].salud -= multiplicador[ATAQUE] / multiplicador[DEFENSA] * FORCEJEO_POTENCIA * personajes[personajeTurno][personajesJugando[personajeTurno]].ataque / personajes[personajeRival][personajesJugando[personajeRival]].defensa;
        personajes[personajeRival][personajesJugando[personajeRival]].salud -= multiplicador[ATAQUE_ESPECIAL] / multiplicador[DEFENSA_ESPECIAL] * FORCEJEO_POTENCIA * personajes[personajeTurno][personajesJugando[personajeTurno]].ataqueEspecial / personajes[personajeRival][personajesJugando[personajeRival]].defensaEspecial;
    }
    else
    {
        personajes[personajeRival][personajesJugando[personajeRival]].salud -= multiplicador[ATAQUE] / multiplicador[DEFENSA] * personajes[personajeTurno][personajesJugando[personajeTurno]].movimiento[movimientos[personajeTurno]].potencia * personajes[personajeTurno][personajesJugando[personajeTurno]].ataque / personajes[personajeRival][personajesJugando[personajeRival]].defensa;
        personajes[personajeRival][personajesJugando[personajeRival]].salud -= multiplicador[ATAQUE_ESPECIAL] / multiplicador[DEFENSA_ESPECIAL] * personajes[personajeTurno][personajesJugando[personajeTurno]].movimiento[movimientos[personajeTurno]].potenciaEspecial * personajes[personajeTurno][personajesJugando[personajeTurno]].ataqueEspecial / personajes[personajeRival][personajesJugando[personajeRival]].defensaEspecial;
    }
    if (personajes[personajeRival][personajesJugando[personajeRival]].salud<0) personajes[personajeRival][personajesJugando[personajeRival]].salud=0;
}

void CalcularMultiplicadores(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], float multiplicador[CANTIDAD_ESTADISTICAS-1], int personajeTurno)
{
    int personajeRival = (personajeTurno==0)?1:0;
    
    multiplicador[ATAQUE]=(float) personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[ATAQUE];
    multiplicador[ATAQUE_ESPECIAL]=(float) personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[ATAQUE_ESPECIAL];
    multiplicador[DEFENSA]=(float) personajes[personajeRival][personajesJugando[personajeRival]].aumentoEstadisticas[DEFENSA];
    multiplicador[DEFENSA_ESPECIAL]=(float) personajes[personajeRival][personajesJugando[personajeRival]].aumentoEstadisticas[DEFENSA_ESPECIAL];
    for (int i=0; i<(CANTIDAD_ESTADISTICAS-1); i++)
    {
        if (multiplicador[i]<0)
            multiplicador[i]=2.0/(2.0-multiplicador[i]);
        else
            multiplicador[i]=(2.0+multiplicador[i])/2.0;
    }
}

void AumentarEstadisticas(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int personajeTurno, int movimientos[JUGADORES])
{
    for (int i=0; i<CANTIDAD_ESTADISTICAS; i++)
    {
        personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[i] += personajes[personajeTurno][personajesJugando[personajeTurno]].movimiento[movimientos[personajeTurno]].aumentoEstadisticas[i];
        if (personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[i]<MIN_AUMENTO_ESTADISTICAS)
            personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[i]=MIN_AUMENTO_ESTADISTICAS;
        if (personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[i]>MAX_AUMENTO_ESTADISTICAS)
            personajes[personajeTurno][personajesJugando[personajeTurno]].aumentoEstadisticas[i]=MAX_AUMENTO_ESTADISTICAS;
    }
}

void AumentarSalud(personaje_t personajes[JUGADORES][MAX_PERSONAJES], int personajesJugando[JUGADORES], int personajeTurno, int movimientos[JUGADORES])
{
    personajes[personajeTurno][personajesJugando[personajeTurno]].salud+=personajes[personajeTurno][personajesJugando[personajeTurno]].saludMaxima * personajes[personajeTurno][personajesJugando[personajeTurno]].movimiento[movimientos[personajeTurno]].aumentoSalud;
    if (personajes[personajeTurno][personajesJugando[personajeTurno]].salud > personajes[personajeTurno][personajesJugando[personajeTurno]].saludMaxima)
        personajes[personajeTurno][personajesJugando[personajeTurno]].salud = personajes[personajeTurno][personajesJugando[personajeTurno]].saludMaxima;
}
