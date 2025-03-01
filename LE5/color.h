//Esta biblioteca permite modificar la apariencia del texto con printf
//La función infoColor() muestra la variación del texto con cada parámetro

#include <stdio.h>

#define RESET "\033[0m"

#define NEGRO "\033[30m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define VIOLETA "\033[35m"
#define CELESTE "\033[36m"
#define BLANCO "\033[37m"

#define NEGRITA "\033[1m"
#define DESVANECIDO "\033[2m"
#define CURSIVA "\033[3m"
#define SUBRAYADO "\033[4m"
#define NEGATIVO "\033[7m"

#define F_NEGRO "\033[40m"
#define F_ROJO "\033[41m"
#define F_VERDE "\033[42m"
#define F_AMARILLO "\033[43m"
#define F_AZUL "\033[44m"
#define F_VIOLETA "\033[45m"
#define F_CELESTE "\033[46m"
#define F_BLANCO "\033[47m"

void infoColor()
{
    printf(RESET "Estos parámetros tienen un efecto en el texto al incluirlos dentro de un printf y se pueden sumar\n");
    printf("RESET" AMARILLO " (elimina los efectos)"  RESET "\n");
    
    printf("\nCOLORES:\n");
    printf(NEGRO "NEGRO" RESET "\n");
    printf(ROJO "ROJO" RESET "\n");
    printf(VERDE "VERDE" RESET "\n");
    printf(AMARILLO "AMARILLO" RESET "\n");
    printf(AZUL "AZUL" RESET "\n");
    printf(VIOLETA "VIOLETA" RESET "\n");
    printf(CELESTE "CELESTE" RESET "\n");
    printf(BLANCO "BLANCO" RESET "\n");
    
    printf("\nEFECTOS:\n");
    printf(NEGRITA "NEGRITA" RESET "\n");
    printf(DESVANECIDO "DESVANECIDO" RESET "\n");
    printf(CURSIVA "CURSIVA" RESET "\n");
    printf(NEGATIVO "NEGATIVO" RESET "\n");
    
    printf("\nFONDOS:\n");
    printf(F_NEGRO "F_NEGRO" RESET "\n");
    printf(F_ROJO "F_ROJO" RESET "\n");
    printf(F_VERDE "F_VERDE" RESET "\n");
    printf(F_AMARILLO "F_AMARILLO" RESET "\n");
    printf(F_AZUL "F_AZUL" RESET "\n");
    printf(F_VIOLETA "F_VIOLETA" RESET "\n");
    printf(F_CELESTE "F_CELESTE" RESET "\n");
    printf(F_BLANCO "F_BLANCO" RESET "\n");
    
    printf("\nEJEMPLO:\n");
    printf(RESET "printf(AMARILLO NEGRITA F_AZUL \"Hola mundo\");");
    printf(RESET "\nImprime: " AMARILLO NEGRITA F_AZUL "Hola mundo" RESET "\n");
}
