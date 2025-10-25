#include <stdio.h>
#include <string.h>
#include "empleado.h"
#include <stdlib.h>

#include "auto.h"

#define ARCHIVO_EMPLEADO "empleado.bin"

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

    printf("Ingrese su contraseña: ");
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
        printf("Correo o contraseña incorrectos.\n");
        return 0;
    }
}

/// funcion 2
int verificar_Usuario(char correo[], char contrasena[])
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
void funcion_iniciarSesion_empleado()
{
    char correo[50], contrasena[50];
    printf("\n------ INICIAR SESION ------\n");
    printf("Correo: ");
    scanf("%s", correo);
    printf("Contrasena: ");
    scanf("%s", contrasena);
    system("cls");

    if(verificar_Usuario(correo, contrasena))
    {
        printf("\nSesion iniciada correctamente\n\n");

        int opcion_sesion;
        do
        {

            /// iria estas opciones para hacer lo otro lo q esta abajo no iria

            printf("-------------------------------------\n");

            printf("1. Datos del cliente \n");
            printf("2. Dato del auto del cliente \n");
            printf("3. Autos disponibles \n");
            printf("4. Pagos \n");
            printf("5. Volver al inicio \n");
            printf("0. Salir \n");



            printf("-------------------------------------\n");

            printf("\n");

            printf("Elija una opcion: ");
            scanf("%d", &opcion_sesion);
            system("cls");

            switch(opcion_sesion)
            {
            case 0:


                printf("Saliendo...\n");

                return ;

                break;
            case 1:

                printf("\n----------------------- \n");
                printf("     DATOS DEL CLIENTE \n");
                printf("-------------------------\n\n");

                /// ACA IRIA EL ARCHIVO Y LA FUNCION DE CARGAR DATOS DEL CLIENTE

                cargar_persona();


                break;
            case 2:
                printf("\n----------------------------- \n");
                printf("   DATO DEL AUTO DEL CLIENTE \n");
                printf("------------------------------\n\n");

                agregar_autos();


                break;
            case 3:

                printf("\n------------------- \n");
                printf("     AUTOS DISPONIBLES \n");
                printf("-----------------------\n\n");

                mostrar_todos_autos(ARCHIVO_AUTOS);


                break;

            case 4 :

                printf("\n------------------- \n");
                printf("     PAGOS \n");
                printf("-----------------------\n\n");

                /// ACA IRA LA EL ARCHIVO DE PAGOS Y LA FUNCION DE LOS PAGOS


                break;

            case 5 :

                printf("Volviendo al inicio...\n");

                opcion_sesion = 0;

                break;



            default:
                printf("Opcion no valida\n");
                break;
            }
        }
        while(opcion_sesion != 0);
    }
    else
    {
        printf("\nCorreo o contrasenia incorrectos\n");
    }
}
