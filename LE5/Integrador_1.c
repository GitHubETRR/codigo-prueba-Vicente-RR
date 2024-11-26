#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define DISPONIBLE 0
#define VENDIDO 1

#define REGISTRAR 1
#define MOSTRAR 2
#define CONSULTAR 3
#define CERRAR 4
#define SALIR 5

#define ASIENTOS 100
#define TAM_TXT 30
#define COSTO 1000

typedef struct{ 

    int dia; 

    int mes; 

    int anio; 

}fecha_venta_t; 


typedef struct{ 

    char nombre[TAM_TXT]; 

    char apellido[TAM_TXT]; 

    fecha_venta_t fecha_venta; 

    bool estado;  		// Estado: DISPONIBLE (0) o VENDIDO (1)	 

}reservas_t; 

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

void VaciarReservas(reservas_t reservas[ASIENTOS]);
int Menu(void);
void Accion(int eleccion, reservas_t reservas[ASIENTOS], int * dinero);
void Mostrar(reservas_t reservas[ASIENTOS], int *dinero);
int ContarAsientosDisponibles(reservas_t reservas[ASIENTOS]);
void MostrarAsientosDisponibles(reservas_t reservas[ASIENTOS]);

int main()
{
    bool salir=false;
    do
    {
        bool reservasAbiertas=true;
        reservas_t reservas[ASIENTOS];
        int dinero=0;
        VaciarReservas(reservas);
        do
        {
            int eleccion=Menu();
            if (eleccion==SALIR)
                salir=true;
            else
                Accion(eleccion, reservas, &dinero);
            if (eleccion==CERRAR)
                reservasAbiertas=false;
        } while ((reservasAbiertas)&&(!salir));
    } while (!salir);

    return 0;
}

void VaciarReservas(reservas_t reservas[ASIENTOS])
{
    for (int i=0; i<ASIENTOS; i++)
        reservas[i].estado=DISPONIBLE;
}

int Menu(void)
{
    int eleccion;
    bool opcionValida;
    
    LimpiarPantalla();
    printf("Menú\n");
    printf("%i - Registrar la venta de un asiento\n", REGISTRAR);
    printf("%i - Mostrar los asientos disponibles\n", MOSTRAR);
    printf("%i - Consultar un asiento\n", CONSULTAR);
    printf("%i - Cerrar las ventas\n", CERRAR);
    printf("%i - Salir\n", SALIR);
    do
    {
        scanf("%i", &eleccion);
        opcionValida = ((eleccion>=REGISTRAR)&&(eleccion<=SALIR));
        if (!opcionValida)
            printf("Por favor, seleccione una opción válida\n");
    } while (!opcionValida);
    LimpiarTeclado();
    LimpiarPantalla();
    
    return eleccion;
}

void Pausa(void)
{
    printf("Enter para continuar...\n");
    getchar();
    LimpiarTeclado();
}

void Accion(int eleccion, reservas_t reservas[ASIENTOS], int *dinero)
{
    switch (eleccion)
    {
        case REGISTRAR:
            {
                Registrar(reservas, dinero);
                break;
            }
        case MOSTRAR:
            {
                Mostrar(reservas, dinero);
                break;
            }
        case CONSULTAR:
            {
                Consultar(reservas);
                break;
            }
        case CERRAR:
            {
                Cerrar(reservas, dinero);
                break;
            }
    }
    Pausa();
}

void Registrar(reservas_t reservas[ASIENTOS], int *dinero)
{
    if (ContarAsientosDisponibles(reservas)==0)
        printf("No hay asientos disponibles\n");
    else
    {
        int nAsiento;
        bool opcionValida;
        
        printf("Ingrese el número de asiento\n");
        do
        {
            scanf("%i", &nAsiento);
            if ((nAsiento>=0)&&(nAsiento<ASIENTOS)&&(reservas[nAsiento].estado==DISPONIBLE))
                opcionValida=true;
            else
            {
                printf("Por favor, seleccione una opción válida\n");
                opcionValida=false;
            }
        } while (!opcionValida);
        LimpiarTeclado();
        reservas[nAsiento].estado=VENDIDO;
        printf("Ingrese el nombre (máx. %i caracteres)\n", TAM_TXT);
        scanf("%s", reservas[nAsiento].nombre);
        LimpiarTeclado();
        printf("Ingrese el apellido (máx. %i caracteres)\n", TAM_TXT);
        scanf("%s", reservas[nAsiento].apellido);
        LimpiarTeclado();
        
        time_t tiempoActual = time(NULL);
        struct tm *tiempo = localtime(&tiempoActual);
        
        reservas[nAsiento].fecha_venta.dia=tiempo->tm_mday;
        reservas[nAsiento].fecha_venta.mes=tiempo->tm_mon+1; //tm_mon tiene los meses del 0 al 11
        reservas[nAsiento].fecha_venta.anio=tiempo->tm_year+1900; //tm_year tiene los años desde 1900
        *dinero+=COSTO;
    }
}

void Mostrar(reservas_t reservas[ASIENTOS], int *dinero)
{
    int asientosDisponibles=ContarAsientosDisponibles(reservas);
    char eleccion;
    printf("Dinero recaudado: %i\n", *dinero);
    printf("Cantidad de asientos disponibles: %i\n", asientosDisponibles);
    if (asientosDisponibles!=0)
    {
        printf("¿Desea ver la lista? (S/N)\n");
        scanf("%c", &eleccion);
        if ((eleccion=='S')||(eleccion=='s'))
            MostrarAsientosDisponibles(reservas);
    }
}

int ContarAsientosDisponibles(reservas_t reservas[ASIENTOS])
{
    int asientosDisponibles=0;
    for (int i=0; i<ASIENTOS; i++)
        if (reservas[i].estado==DISPONIBLE)
            asientosDisponibles++;
    
    return asientosDisponibles;
}

void MostrarAsientosDisponibles(reservas_t reservas[ASIENTOS])
{
    for (int i=0; i<ASIENTOS; i++)
        if (reservas[i].estado==DISPONIBLE)
            printf("%i ", i);
    printf("\n");
}

void Consultar(reservas_t reservas[ASIENTOS])
{
    int nAsiento;
    bool opcionValida;
    printf("Ingrese el número de asiento\n");
    do
    {
        scanf("%i", &nAsiento);
        if ((nAsiento>=0)&&(nAsiento<ASIENTOS))
            opcionValida=true;
        else
        {
            printf("Por favor, seleccione una opción válida\n");
            opcionValida=false;
        }
        
    } while (!opcionValida);
    if (reservas[nAsiento].estado==DISPONIBLE)
        printf("El asiento está disponible\n");
    else
        printf("El asiento fue comprado por %s %s el %i/%i/%i\n", reservas[nAsiento].nombre, reservas[nAsiento].apellido, reservas[nAsiento].fecha_venta.dia, reservas[nAsiento].fecha_venta.mes, reservas[nAsiento].fecha_venta.anio);
}

void Cerrar(reservas_t reservas[ASIENTOS], int *dinero)
{
    int asientosVendidos=ASIENTOS-ContarAsientosDisponibles(reservas);
    printf("Dinero recaudado: %i\n", *dinero);
    printf("Porcentaje de ocupación: %i%\n", (100*asientosVendidos/ASIENTOS));
}
