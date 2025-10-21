
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"

// FUNCION 1
int usuario_existente(char correo[])
{
    FILE* file = fopen(ARCHIVO_CLIENTES, "rb");
    if(file == NULL) return 0;

    stUsuario usuario;
    while(fread(&usuario, sizeof(stUsuario), 1, file) == 1)
    {
        if(strcmp(usuario.correo, correo) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// FUNCION 2
stUsuario registro_Usuario()
{
    stUsuario nuevo;

    printf("\n--- REGISTRO DE USUARIO ---\n");
    printf("Ingrese su correo: ");
    scanf("%49s", nuevo.correo);

    if(usuario_existente(nuevo.correo))
    {
        printf("Este usuario ya está registrado\n");
        nuevo.dni = -1;
        return nuevo;
    }

    printf("Ingrese su contraseña: ");
    scanf("%49s", nuevo.contrasena);

    printf("Ingrese su DNI: ");
    scanf("%d", &nuevo.dni);

    printf("Fecha de nacimiento (dd mm aaaa): ");
    scanf("%d %d %d", &nuevo.dia, &nuevo.mes, &nuevo.anios);

    printf("\nUsuario registrado con éxito\n");
    return nuevo;
}

// FUNCION 3
void guardar_Usuario(stUsuario usuario)
{
    FILE *file = fopen(ARCHIVO_CLIENTES, "ab");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(&usuario, sizeof(stUsuario), 1, file);
    fclose(file);
}

// FUNCION 4
int verificar_Usuario(char correo[], char contrasena[])
{
    FILE *file = fopen(ARCHIVO_CLIENTES, "rb");
    if(file == NULL)
    {
        return 0;
    }
    stUsuario usuario;
    int encontrado = 0;
    while(fread(&usuario, sizeof(stUsuario), 1, file) > 0)
    {
        if(strcmp(usuario.correo, correo) == 0 && strcmp(usuario.contrasena, contrasena) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    fclose(file);
    return encontrado;
}

// FUNCION 5
void iniciarSesion()
{
    char correo[50], contrasena[50];
    printf("\n------ INICIAR SESION ------\n");
    printf("Correo: ");
    scanf("%s", correo);
    printf("Contraseña: ");
    scanf("%s", contrasena);
    system("cls");

    if(verificar_Usuario(correo, contrasena))
    {
        printf("\nSesion iniciada correctamente\n\n");
        /// ACÁ VA EL MENÚ INTERNO (todavía no lo copié)
    }
    else
    {
        printf("\nCorreo o contraseña incorrectos\n");
    }
}



