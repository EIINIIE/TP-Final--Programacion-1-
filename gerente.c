#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gerente.h"
#include "empleado.h"

/// #define ARCHIVO_GERENTE "gerente.bin"

//-----------------------------------------------------
// FUNCION 1 - Iniciar sesion del gerente (administrador)
//-----------------------------------------------------
int iniciarSesionGerente()
{
    stGerente gerente;

    strcpy(gerente.correo, "admin@gmail.com");
    strcpy(gerente.contrasena,"admin101");
    strcpy(gerente.rol,"administrador");

    char correoIngresado[50];
    char contrasenaIngresada[50];

    printf("Ingrese su correo: ");
    fflush(stdin);
    gets(correoIngresado);

    printf("Ingrese su contrasena: ");
    fflush(stdin);
    gets(contrasenaIngresada);

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


///-----------------------------------------------------
/// FUNCION 2 - Menu del gerente
///-----------------------------------------------------
void menu_gerente()
{
    int opcion;

    do
    {
        printf("\n-----------------------------------\n");
        printf("         MENU DEL GERENTE\n");
        printf("-----------------------------------\n");
        printf("1. Registrar nuevo empleado\n");
        printf("2. Ver empleados\n");
        printf("3. Eliminar empleado\n");
        printf("0. Cerrar sesion\n");
        printf("-----------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1:
            agregar_empleado();
            break;

        case 2:
            mostrar_empleados();
            break;

        case 3:
            eliminar_empleado();
            break;

        case 0:
            printf("Cerrando sesion...\n");
            break;

        default:
            printf("Opcion invalida.\n");
            break;
        }

        if (opcion != 0)
        {
            system("pause");
            system("cls");
        }

    }
    while (opcion != 0);
}

//-----------------------------------------------------
// FUNCION 3 - Cargar un empleado nuevo
//-----------------------------------------------------
stGerente cargar_un_empleado()
{
    stGerente nuevo;

    printf("---- REGISTRO DE NUEVO EMPLEADO ----\n");

    printf("Ingrese correo: \n");
    scanf("%s", nuevo.correo);

    printf("Ingrese contrasena: \n");
    scanf("%s", nuevo.contrasena);

    printf("Ingrese DNI: \n");
    scanf("%d", &nuevo.dni);

    printf("Ingrese dia de nacimiento: \n");
    scanf("%d", &nuevo.dia);

    printf("Ingrese mes de nacimiento: \n");
    scanf("%d", &nuevo.mes);

    printf("Ingrese anio de nacimiento: \n");
    scanf("%d", &nuevo.anios);

    printf("Ingrese rol (ej: vendedor, mecanico, etc): \n");
    scanf("%s", nuevo.rol);

    return nuevo;
}

//-----------------------------------------------------
// FUNCION 4 - Agregar empleado al archivo
//-----------------------------------------------------
void agregar_empleado()
{
    FILE* file = fopen(ARCHIVO_EMPLEADOS, "ab");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de empleados.\n");
        return;
    }

    char control = 's';
    while (control == 's')
    {
        stGerente nuevo = cargar_un_empleado();
        fwrite(&nuevo, sizeof(stGerente), 1, file);

        printf("Empleado registrado con exito.\n");
        printf("Desea registrar otro empleado? (s/n): ");
        fflush(stdin);
        scanf(" %c", &control);
    }

    fclose(file);
    printf("Registros completados.\n");
}

//-----------------------------------------------------
// FUNCION 5 - Eliminar empleado por DNI
//-----------------------------------------------------
void eliminar_empleado()
{
    FILE* file = fopen(ARCHIVO_EMPLEADOS, "r+b");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo de empleados.\n");
        return;
    }

    int buscar_dni;
    printf("Ingrese el DNI del empleado a eliminar: ");
    scanf("%d", &buscar_dni);

    stGerente emple;
    int encontrado = 0;

    while (fread(&emple, sizeof(stGerente), 1, file) == 1)
    {
        if (emple.dni == buscar_dni)
        {
            encontrado = 1;
            printf("Empleado encontrado: %s | Rol: %s\n", emple.correo, emple.rol);
            printf("Desea confirmar la eliminacion? (1 = Si / 2 = No): ");
            int confirmar;
            scanf("%d", &confirmar);

            if (confirmar == 1)
            {
                stGerente vacio = {0};
                fseek(file, -sizeof(stGerente), SEEK_CUR);
                fwrite(&vacio, sizeof(stGerente), 1, file);
                printf("Empleado eliminado correctamente.\n");
            }
            else
            {
                printf("Operacion cancelada.\n");
            }
            break;
        }
    }

    if (!encontrado)
    {
        printf("No se encontro un empleado con ese DNI.\n");
    }

    fclose(file);
}

//-----------------------------------------------------
// FUNCION 6 - Mostrar empleados cargados
//-----------------------------------------------------
void mostrar_empleados()
{
    FILE* file = fopen(ARCHIVO_EMPLEADOS, "rb");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo de empleados.\n");
        return;
    }

    stGerente emple;
    int contador = 0;

    printf("-------- LISTA DE EMPLEADOS CARGADOS --------\n");

    while (fread(&emple, sizeof(stGerente), 1, file) == 1)
    {
        if (emple.dni != 0)
        {
            printf("Empleado #%d\n", ++contador);
            printf("DNI: %d\n", emple.dni);
            printf("Correo: %s\n", emple.correo);
            printf("Rol: %s\n", emple.rol);
            printf("--------------------------------------------\n");
        }
    }

    fclose(file);
}
