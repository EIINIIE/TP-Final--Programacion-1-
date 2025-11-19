#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LOING.h"
#include "usuario.h"
#include "empleado.h"
#include "gerente.h"

/// #define ARCHIVO_EMPLEADO "empleado.bin"

void menu_login()
{
    int opcion_login;

    do
    {
        printf("\n-------------------------------------\n");
        printf("            MENU LOGIN\n");
        printf("-------------------------------------\n");
        printf("1. EMPRESA\n"); /// este seria para el empleado
        printf("2. CLIENTE\n");
        printf("3. ADMINISTRADOR\n"); /// aca nose si poner el administrador o gerente
        printf("0. Volver al inicio\n");
        printf("-------------------------------------\n");

        printf("\nElija una opcion: ");
        scanf("%d", &opcion_login);

        getchar(); // <-- Esta es tu correccion, esto perfecta.
        system("cls");

        switch (opcion_login)
        {
        case 1:
            printf("Iniciando sesion como EMPRESA...\n");
            login_empresa(); /// <-- Llama a la funcion SOLO de empleados
            break;

        case 2:
        {
            int opcion_cliente;
            do
            {
                printf("\n-------------------------------------\n");
                printf("         ACCESO CLIENTE\n");
                printf("---------------------------------------\n");
                printf("1. Iniciar sesion\n");
                printf("2. Registrarse\n");
                printf("0. Volver atras\n");
                printf("-------------------------------------\n");
                printf("\nElija una opcion: ");
                scanf("%d", &opcion_cliente);

                getchar(); // <-- Esta es tu correccion, esto perfecta.
                system("cls");

                switch (opcion_cliente)
                {
                case 1:
                    iniciarSesion(); /// usuario.c
                    break;

                case 2:
                {
                    stUsuario nuevo = registro_Usuario();
                    if (nuevo.dni != -1) /// se registro correctamente
                    {
                        guardar_Usuario(nuevo);
                        printf("\nAhora inicie sesion con su nuevo usuario.\n\n");
                        system("pause");
                        system("cls");
                        iniciarSesion(); /// usuario.c
                    }
                    break;
                }

                case 0:
                    printf("Volviendo atras...\n");
                    opcion_cliente = 0;
                    break;

                default:
                    printf("Opcion no valida.\n");
                    break;
                }

                system("pause");
                system("cls");

            }
            while (opcion_cliente != 0);
        }
        break;

        case 3 :

            printf("Iniciado como administrador \n");
            login_administrador();

            break;

        case 0:
            printf("Volviendo al inicio...\n");
            break;

        default:
            printf("Opcion no valida.\n");
            break;
        }

        system("pause");
        system("cls");

    }
    while (opcion_login != 0);
}

// --- FUNCION SOLO PARA ADMINISTRADOR ---
void login_administrador()
{
    char correo[50];
    char contrasena[50];

    printf("----iniciar sesion administrador----\n");
    printf("correo: ");
    fflush(stdin);
    gets(correo);
    correo[strcspn(correo, "\n")] = 0;
    printf("contrasena: ");
    fflush(stdin);
    gets(contrasena);
    contrasena[strcspn(contrasena, "\n")] = 0;

    system("cls");

    // Logica movida desde login_empresaa
    if (strcmp(correo, "admin@gmail.com") == 0 && strcmp(contrasena, "admin101") == 0)
    {
        printf("Inicio de sesion exitoso - Rol: ADMINISTRADOR\n");
        menu_gerente();
        return;
    }
    else
    {
        printf("Correo o contrasena incorrectos.\n");
    }
}

void login_empresa()
{
    char correo[50];
    char contrasena[50];

    printf("----iniciar sesion empresa----\n");
    printf("correo: ");
    fflush(stdin);
    gets(correo);
    correo[strcspn(correo, "\n")] = 0;
    printf("contrasena: ");
    fflush(stdin);
    gets(contrasena);
    contrasena[strcspn(contrasena, "\n")] = 0;

    system("cls");

    /* esta logica se movio a login_administrador
    if (strcmp(correo, "admin@gmail.com") == 0 && strcmp(contrasena, "admin101") == 0)
    {
        printf("Inicio de sesion exitoso - Rol: ADMINISTRADOR\n");
        menu_gerente();
        return;
    }
    */
    FILE* file = fopen(ARCHIVO_EMPLEADOS, "rb");
    //rewind(file);
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo de empleados.\n");
        return;
    }

    stEmpleado emple;
    int encontrado = 0;

    while (fread(&emple, sizeof(stEmpleado), 1, file) == 1)
    {
        if (strcmp(correo, emple.correo) == 0 && strcmp(contrasena, emple.contrasena) == 0)
        {
            encontrado = 1;
            printf("Inicio de sesion exitoso – Rol: %s\n", emple.rol);
            system("pause");
            system("cls");

            if (strcmp(emple.rol, "administrador") == 0)
            {
                menu_gerente();
            }
            else
            {
                menu_empleado_directo(); // función sin login otra vez
            }
            break;
        }
    }
}
