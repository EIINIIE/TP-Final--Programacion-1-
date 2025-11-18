#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "empleado.h"
#include "auto.h"
#include "auto_cliente.h" // Para agregar_autos
#include "autos_disponibles.h"
#include "cliente.h" // Para cargar_persona
#include "pagos.h"


//#define ARCHIVO_EMPLEADO "empleado.bin"

/// funcion 1

int iniciarSesion_empleado()
{
    stEmpleado empleado;



    strcpy(empleado.correo, "empleado_123@gmail.com");
    strcpy(empleado.contrasena, "empleado123");


    char correoIngresado[50];
    char contrasenaIngresada[50];

    printf("Ingrese su correo: ");
    scanf("%s", correoIngresado);

    printf("Ingrese su contrasena: ");
    scanf("%s", contrasenaIngresada);

    system("cls");

    if (strcmp(correoIngresado, empleado.correo) == 0 &&
            strcmp(contrasenaIngresada, empleado.contrasena) == 0)
    {
        printf("Inicio de sesion exitoso!\n");
        return 1;
    }
    else
    {
        printf("Correo o contrasena incorrectos.\n");
        return 0;
    }
}

/// funcion 2
int verificar_Usuario_empleado(char correo[], char contrasena[])
{
    stEmpleado empleado;
    strcpy(empleado.correo, "empleado_123@gmail.com");
    strcpy(empleado.contrasena, "empleado123");

    if (strcmp(correo, empleado.correo) == 0 &&
            strcmp(contrasena, empleado.contrasena) == 0)
    {
        return 1;
    }
    return 0;
}

/// ------------------------------------------------------------------------------------------------------

/// FUNCION 3
void menu_empleado_directo()
{
    int opcion_sesion;
    do
    {
        printf("-------------------------------------\n");
        printf("1. Datos del cliente \n");
        printf("2. Dato del auto del cliente \n");
        printf("3. Autos disponibles \n");
        printf("4. Pagos \n");
        printf("5. Volver al inicio \n");
        printf("0. Salir \n");
        printf("-------------------------------------\n\n");

        printf("Elija una opcion: ");
        scanf("%d", &opcion_sesion);
        system("cls");

        switch(opcion_sesion)
        {
            case 0:
                printf("Saliendo...\n");
                return;

            case 1:
                cargar_persona();
                break;

            case 2:
                agregar_autos_cliente();
                break;

            case 3:
                mostrar_todos_autos_disponibles();
                break;

            case 4:
                gestionDePagos();
                break;

            case 5:
                opcion_sesion = 0;
                break;

            default:
                printf("Opcion no valida\n");
                break;
        }

    } while(opcion_sesion != 0);
}
