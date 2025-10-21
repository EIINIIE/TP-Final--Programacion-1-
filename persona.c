#include <stdio.h>
#include <string.h>
#include "persona.h"

// FUNCION 1
Persona cargar_persona()
{
    Persona datos;

    printf("----DATOS DEL TITULAR----\n");
    printf("DNI: ");
    scanf("%s", datos.dni);
    printf("Nombre: ");
    fflush(stdin);
    gets(datos.nombre);
    printf("Telefono: ");
    scanf("%s", datos.telefono);
    printf("Direccion: ");
    fflush(stdin);
    gets(datos.direccion);
    printf("Rol: ");
    scanf("%s", datos.rol);
    printf("------------------------\n\n");

    return datos;
}
