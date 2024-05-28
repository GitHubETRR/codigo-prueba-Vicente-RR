#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
int victorias;
int derrotas;

//Defino las funciones para que no tengan que estar en orden
bool preguntarJugarDeNuevo(void); 
int jugarPartida(void);
int dibujarTablero(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9);
char preguntarCasilla(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9);
bool verificarGanador(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9);
int fin(bool victoria);
char elegirCasillaCPU(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9);

int main(void)
{
    bool jugarDeNuevo;
    
    srand(time(NULL));  //Usa la hora como semilla para los números aleatorios
    do
    {
        jugarPartida();
        jugarDeNuevo = preguntarJugarDeNuevo();
    } while (jugarDeNuevo);
}

int jugarPartida(void)
{
    char c1 = 0;
    char c2 = 0;
    char c3 = 0;
    char c4 = 0;
    char c5 = 0;
    char c6 = 0;
    char c7 = 0;
    char c8 = 0;
    char c9 = 0;
    char casillaElegida;
    char casillaCPU;
    char jugadas = 0;
    bool finPartida;
    
    do
    {
        dibujarTablero(c1, c2, c3, c4, c5, c6, c7, c8, c9);
        casillaElegida = preguntarCasilla(c1, c2, c3, c4, c5, c6, c7, c8, c9);
        switch (casillaElegida)
        {
            case 1:
                c1 = 1;
            break;
            case 2:
                c2 = 1;
            break;
            case 3:
                c3 = 1;
            break;
            case 4:
                c4 = 1;
            break;
            case 5:
                c5 = 1;
            break;
            case 6:
                c6 = 1;
            break;
            case 7:
                c7 = 1;
            break;
            case 8:
                c8 = 1;
            break;
            case 9:
                c9 = 1;
            break;
        }
        jugadas++;
        finPartida = verificarGanador(c1, c2, c3, c4, c5, c6, c7, c8, c9);
        if (finPartida) //Si ganó el jugador
        {
            dibujarTablero(c1, c2, c3, c4, c5, c6, c7, c8, c9);
            fin(true); //True indica que la victoria es del jugador
        }
        else    //Si todavía no ganó, juega el CPU
        {
            if (jugadas<9) //Si no se agotaron las jugadas
            {
                casillaCPU = elegirCasillaCPU(c1, c2, c3, c4, c5, c6, c7, c8, c9);
                switch (casillaCPU)
                {
                case 1:
                    c1 = 2;
                break;
                case 2:
                    c2 = 2;
                break;
                case 3:
                    c3 = 2;
                break;
                case 4:
                    c4 = 2;
                break;
                case 5:
                    c5 = 2;
                break;
                case 6:
                    c6 = 2;
                break;
                case 7:
                    c7 = 2;
                break;
                case 8:
                    c8 = 2;
                break;
                case 9:
                    c9 = 2;
                break;
                }
                jugadas++;
                finPartida = verificarGanador(c1, c2, c3, c4, c5, c6, c7, c8, c9);
                if (finPartida) //Si ganó el CPU
                {
                    dibujarTablero(c1, c2, c3, c4, c5, c6, c7, c8, c9);
                    fin(false); //False indica que la victoria es del CPU
                }
            }
            else
            {
                dibujarTablero(c1, c2, c3, c4, c5, c6, c7, c8, c9);
                printf("Empate.\n");
                finPartida = true;
            }
        }
    } while (!finPartida);
}

int dibujarTablero(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9)
{
    printf("\n");
    switch (c1)
    {
        case 0:
            printf("1");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf(" | ");
    switch (c2)
    {
        case 0:
            printf("2");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf(" | ");
    switch (c3)
    {
        case 0:
            printf("3");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf("\n---------\n");
    switch (c4)
    {
        case 0:
            printf("4");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf(" | ");
    switch (c5)
    {
        case 0:
            printf("5");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf(" | ");
    switch (c6)
    {
        case 0:
            printf("6");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf("\n---------\n");
    switch (c7)
    {
        case 0:
            printf("7");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf(" | ");
    switch (c8)
    {
        case 0:
            printf("8");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf(" | ");
    switch (c9)
    {
        case 0:
            printf("9");
        break;
        case 1:
            printf("X");
        break;
        case 2:
            printf("O");
        break;
    }
    printf("\n\n");
}

bool verificarGanador(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9)
{
    // Combinaciones ganadoras
    if ((c1 == c2 && c2 == c3 && c1 !=0) || // fila superior
        (c4 == c5 && c5 == c6 && c4 !=0) || // fila media
        (c7 == c8 && c8 == c9 && c7 !=0) || // fila inferior
        (c1 == c4 && c4 == c7 && c1 !=0) || // columna izquierda
        (c2 == c5 && c5 == c8 && c2 !=0) || // columna media
        (c3 == c6 && c6 == c9 && c3 !=0) || // columna derecha
        (c1 == c5 && c5 == c9 && c1 !=0) || // diagonal principal
        (c3 == c5 && c5 == c7 && c3 !=0))   // diagonal secundaria
    {
        return true;  // Alguien ganó
    }
    else
    {
        return false;  // Nadie ha ganado todavía
    }
}

char preguntarCasilla(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9)
{
    bool casillaValida;
    char casilla;

    printf("Elegi una casilla para marcar indicando su numero \n");
    do
    {
        casilla = getch();
        switch (casilla)
        {
            case '1':
                casillaValida = (c1==0) ? true:false;
            break;
            case '2':
                casillaValida = (c2==0) ? true:false;
            break;
            case '3':
                casillaValida = (c3==0) ? true:false;
            break;
            case '4':
                casillaValida = (c4==0) ? true:false;
            break;
            case '5':
                casillaValida = (c5==0) ? true:false;
            break;
            case '6':
                casillaValida = (c6==0) ? true:false;
            break;
            case '7':
                casillaValida = (c7==0) ? true:false;
            break;
            case '8':
                casillaValida = (c8==0) ? true:false;
            break;
            case '9':
                casillaValida = (c9==0) ? true:false;
            break;
            default:
                casillaValida = false;
        }
        if (!casillaValida)
        {
            printf("Introduci una casilla valida \n");
        }
    } while (!casillaValida);
    casilla = casilla-48; //Como el valor de la variable casilla fue introducido por el teclado, está en ASCII. Al restarle 48 a los ASCII de los dígitos, este vale lo mismo que el dígito.
    return casilla;
}

char elegirCasillaCPU(char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9)
{
    char casillaAleatoria;

    do
    {
        casillaAleatoria = rand() % 10; //Toma un valor aleatorio del 1 al 9
    } while ((casillaAleatoria==0) || //Comprueba si vale 0, que no es válido
    (casillaAleatoria==1 && c1!=0) || //Comprueba si está disponible la casilla elegida aleatoriamente
    (casillaAleatoria==2 && c2!=0) ||
    (casillaAleatoria==3 && c3!=0) ||
    (casillaAleatoria==4 && c4!=0) ||
    (casillaAleatoria==5 && c5!=0) ||
    (casillaAleatoria==6 && c6!=0) ||
    (casillaAleatoria==7 && c7!=0) ||
    (casillaAleatoria==8 && c8!=0) ||
    (casillaAleatoria==9 && c9!=0));
    return casillaAleatoria;
}

int fin(bool victoria)
{
    if (victoria) //Si ganó el jugador
    {
        printf("Felicitaciones, ganaste!\n");
        victorias ++;
    }
    else    //Si ganó el CPU
    {
        printf("Perdiste!\n");
        derrotas++;
    }
    printf("Victorias: %i \nDerrotas: %i\n", victorias, derrotas);
}

bool preguntarJugarDeNuevo(void)
{
    bool jugarDeNuevo;
    char tecla;
    
    printf("Si deseas jugar de nuevo, presiona la tecla espacio \n");
    tecla = getch();
    jugarDeNuevo = (tecla==' ') ? true:false; //Operador ternario: le da un valor a la variable indicada dependiendo de si se cumple o no la condición
    return jugarDeNuevo;
}
