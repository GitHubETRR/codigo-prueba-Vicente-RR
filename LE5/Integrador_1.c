#include <stdio.h>
#include <stdbool.h>

#define DISPONIBLE 0
#define VENDIDO 1

#define REGISTRAR 1
#define MOSTRAR 2
#define CONSULTAR 3
#define CERRAR 4
#define SALIR 5

#define ASIENTOS 100
#define TAM_TXT 30

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
    bool usar;
    
    do
    {
        reservas_t reservas[ASIENTOS];
        int dinero=0;
        int eleccion=Menu();
        VaciarReservas(reservas);
        if (eleccion==SALIR)
            usar=false;
        else
            Accion(eleccion, reservas, &dinero);
    } while (usar);

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

void Accion(int eleccion, reservas_t reservas[ASIENTOS], int *dinero)
{
    switch (eleccion)
    {
        case REGISTRAR:
            {
                break;
            }
        case MOSTRAR:
            {
                Mostrar(reservas, dinero);
                break;
            }
        case CONSULTAR:
            {
                break;
            }
        case CERRAR:
            {
                break;
            }
    }
}

void Mostrar(reservas_t reservas[ASIENTOS], int *dinero)
{
    int asientosDisponibles=ContarAsientosDisponibles(reservas);
    char eleccion;
    printf("Dinero recaudado: %i\n", *dinero);
    printf("Cantidad de asientos disponibles: %i\n", asientosDisponibles);
    printf("¿Desea ver la lista? (S/N)\n");
    scanf("%c", &eleccion);
    if ((eleccion=='S')||(eleccion=='s'))
        MostrarAsientosDisponibles(reservas);
}

int ContarAsientosDisponibles(reservas_t reservas[ASIENTOS])
{
    int asientosDisponibles=0;
    for (int i=0; i<ASIENTOS; i++)
        if (reservas[i].estado==VENDIDO)
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
