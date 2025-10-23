#include <stdio.h>
#include <string.h>
#include "gerente.h"

// FUNCION 1
int iniciarSesionGerente()
{
    stGerente gerente;

    strcpy(gerente.correo, "admin@gmail.com");
    strcpy(gerente.contrasena,"admin101");

    char correoIngresado[50];
    char contrasenaIngresada[50];

    printf("Ingrese su correo: ");
    scanf ("%s", correoIngresado);

    printf("Ingrese su contraseña: ");
    scanf("%s", contrasenaIngresada);

    if (strcmp (correoIngresado, gerente.correo) == 0 && strcmp(contrasenaIngresada, gerente.contrasena) == 0)
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
