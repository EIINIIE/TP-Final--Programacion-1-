#include <stdio.h>
#include <stdlib.h>
#include <string.h> /// esto no se si sacarlo
#include <time.h> // Para números random

#define ARCHIVO_CLIENTES "clientes.bin"*/ /// lo pongo para ver
#define ARCHIVO_AUTOS "autos.bin" /// lo pongo para ver


/// librerias agregadas
/// usuario
#include "usuario.h"
/// persona
#include "persona.h"
/// auto
#include "auto.h"

/// ---------------------------------------------------------------------------------------

/// MAIN
int main()
{

    srand(time(NULL));
    int opcion;
    do
    {
        printf("\n-------------------------------------------------\n");
        printf("     SISTEMA DE USUARIOS - COMPANIA DE AUTOS UNT \n");
        printf("---------------------------------------------------\n\n");
        printf("1. Iniciar sesion\n");
        printf("2. Registrarse\n");
        printf("3. Cargar autos manualmente\n");
        printf("4. \n");
        printf("0. Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        system("cls");

        switch(opcion)
        {
        case 0:
            printf("Saliendo del sistema...\n");
            break;
        case 1:
            iniciarSesion();
            break;
        case 2:
        {
            stUsuario nuevo = registro_Usuario();
            if(nuevo.dni != -1)
            {
                guardar_Usuario(nuevo);
            }
        }
        break;

        case 3:
            agregar_autos();
            break;

        case 4:

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

/// fin
