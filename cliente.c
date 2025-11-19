#include <stdio.h>
#include <string.h>
#include "cliente.h"

#define ARCHIVO_CLIENTES "clientes.bin"

// FUNCION 1: Cargar en memoria
Cliente cargar_persona()
{
    Cliente datos;

    printf("---- DATOS DEL CLIENTE ----\n");
    printf("DNI: ");
    scanf("%s", datos.dni);
    printf("Nombre: ");
    scanf("%s", datos.nombre);
    printf("Telefono: ");
    scanf("%s", datos.telefono);
    printf("Direccion: ");
    scanf("%s", datos.direccion);
    printf("Rol: ");
    scanf("%s", datos.rol);

    printf("------------------------\n\n");
    return datos;
}

// FUNCION 2: Guardar en archivo
void guardar_cliente_en_archivo(Cliente c)
{
    FILE *file = fopen(ARCHIVO_CLIENTES, "ab");
    if(file != NULL)
    {
        fwrite(&c, sizeof(Cliente), 1, file);
        fclose(file);
        printf("\n[EXITO] Cliente guardado correctamente.\n");
    }
    else
    {
        printf("Error al abrir archivo.\n");
    }
}

// FUNCION 3: Modificar cliente
void modificar_cliente()
{
    char dniBuscado[30];
    printf("\n--- MODIFICAR CLIENTE ---\n");
    printf("Ingrese DNI del cliente a modificar: ");
    scanf("%s", dniBuscado);

    FILE *f = fopen(ARCHIVO_CLIENTES, "rb+");
    if(f == NULL)
    {
        printf("No se pudo abrir el archivo de clientes.\n");
        return;
    }

    Cliente c;
    int encontrado = 0;

    while(fread(&c, sizeof(Cliente), 1, f) == 1)
    {
        // Eliminamos posibles espacios al final del DNI
        c.dni[strcspn(c.dni, "\n")] = 0; /// Sacarlo ?
        c.dni[strcspn(c.dni, " ")] = 0; /// Sacarlo ?

        if(strcmp(c.dni, dniBuscado) == 0)
        {
            encontrado = 1;

            printf("\nCliente encontrado:\n");
            printf("Nombre actual: %s\n", c.nombre);
            printf("Telefono actual: %s\n", c.telefono);
            printf("Direccion actual: %s\n", c.direccion);
            printf("Rol actual: %s\n", c.rol);

            fflush(stdin); // limpiar buffer

            printf("\nIngrese nuevo nombre: ");
            scanf("%s", c.nombre);
            printf("Ingrese nuevo telefono: ");
            scanf("%s", c.telefono);
            printf("Ingrese nueva direccion: ");
            scanf("%s", c.direccion);
            printf("Ingrese nuevo rol: ");
            scanf("%s", c.rol);

            fseek(f, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, f);

            printf("\nCliente modificado correctamente.\n");
            break;
        }
    }

    if(encontrado == 0)
    {
        printf("\nNo se encontro un cliente con DNI: %s\n", dniBuscado);
    }

    fclose(f);
}
