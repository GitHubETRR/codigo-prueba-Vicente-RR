#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

typedef enum {
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
void IngresarPersonaje(void);
void ImprimirPersonaje(personaje_t * personaje);
void MostrarLista(void);
void GuardarDatos(void);
void LiberarMemoria(void);
void LimpiarTeclado(void);
void LimpiarPantalla(void);

//JUEGO
void Turno(personaje_t personajes[2], movimiento_t movimientos[2]);
int CompararVelocidades(personaje_t personajes[2]);
void Atacar(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);
void CalcularMultiplicadores(personaje_t personajes[2], float multiplicador[CANTIDAD_ESTADISTICAS-1], int personajeTurno);
void AumentarEstadisticas(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);
void AumentarSalud(personaje_t personajes[2], int personajeTurno, movimiento_t movimientos[2]);

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
        printf("1_Ingresar un personaje\n");
        printf("2_Mostrar toda la lista\n");
        printf("3_Eliminar un personaje\n");
        printf("4_Editar un personaje\n");
        printf("5_Guardar los personajes\n");
        printf("6_Salir\n");
        scanf("%d", &op);
        LimpiarTeclado();
        LimpiarPantalla();
        switch (op)
        {
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
    int id=1;
    while (lista!=NULL)
    {
        lista->id=id;
        lista=lista->next;
        id++;
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
        printf("MOVIMIENTO %i: %s\n", (i+1), personaje_ptr->movimiento[i].nombre);
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

void ImprimirPersonaje(personaje_t * personaje)
{
    printf("\n--------------------\n");
    printf("ID: %i\n",personaje->id);
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

void MostrarLista(void)
{
    personaje_t * lista=lista_personajes;
    while(lista!=NULL)
    {
        ImprimirPersonaje(lista);
        lista=lista->next;
    }
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
