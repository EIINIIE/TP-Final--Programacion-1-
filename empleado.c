#include <stdio.h>
#include <string.h>
#include "empleado.h"

/// FUNCION 1

int iniciarSesion_empleado()
{
    stEmpreado empreado;

    strcpy(empreado.correo, "empleado_123@gmail.com");
    strcpy(empreado.contrasena,"empleado123");

    char correoIngresado[50];
    char contrasenaIngresada[50];

    printf("Ingrese su correo: ");
    scanf ("%s", correoIngresado);

    printf("Ingrese su contraseña: ");
    scanf("%s", contrasenaIngresada);

    if (strcmp (correoIngresado, empreado.correo) == 0 && strcmp(contrasenaIngresada, empreado.contrasena) == 0)
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
