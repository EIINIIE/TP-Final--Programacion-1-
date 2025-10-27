#include <stdio.h>
#include <stdlib.h>
#include <string.h> /// esto no se si sacarlo
#include <time.h> // Para números random

#define ARCHIVO_CLIENTES "clientes.bin" /// lo pongo para ver
#define ARCHIVO_AUTOS "autos.bin" /// lo pongo para ver

/// librerias agregadas
/// usuario
#include "usuario.h" /// esto seria de la parte del empleado
/// Cliente
#include "cliente.h"
/// auto
#include "auto.h"
/// empleado.
#include "empleado.h"
/// loing
#include "LOING.h"
/// ---------------------------------------------------------------------------------------

/// MAIN
int main()
{

    srand(time(NULL));
    int opcion;
    do
    {

        printf("\n---------------------------------------------------\n");
        printf("     SISTEMA DE USUARIOS - COMPANIA DE AUTOS UNT \n");
        printf("---------------------------------------------------\n\n");
        printf("1. INGRESAR \n");
        printf("0. Salir\n");

        printf("----------------------------------------------------\n");

        printf("\n");

        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 0:
            printf("Saliendo del sistema...\n");
            break;
        case 1:

            menu_login();

            break;

        default:
            printf("Opción no válida\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(opcion != 0);

    return 0;
}

/// Fin
