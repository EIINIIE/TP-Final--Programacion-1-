#include <stdio.h>
#include <string.h>
#include "cliente.h"


/// esto ya estaria

/// FUNCION 1
Cliente cargar_persona()
{
    Cliente datos;

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
   scanf("%s", datos.direccion);
    printf("Rol: ");
    fflush(stdin);
    scanf("%s", datos.rol);
    printf("------------------------\n\n");

    return datos;
}




