#include <stdio.h>
#include <stdlib.h>
#include "LOING.h"
#include "usuario.h"
#include "empleado.h"

void menu_login()
{
    int opcion_login;

    do
    {
        printf("\n-------------------------------------\n");
        printf("            MENU LOGIN\n");
        printf("-------------------------------------\n");
        printf("1. EMPRESA\n");
        printf("2. CLIENTE\n");
        printf("0. Volver al inicio\n");
        printf("-------------------------------------\n");

        printf("\nElija una opción: ");
        scanf("%d", &opcion_login);
        system("cls");

        switch (opcion_login)
        {
        case 1:
            printf("Iniciando sesión como EMPRESA...\n");
            iniciarSesion_empleado(); /// función del archivo empleado.c
            break;

        case 2:
        {
            int opcion_cliente;
            do
            {
                printf("\n-------------------------------------\n");
                printf("         ACCESO CLIENTE\n");
                printf("---------------------------------------\n");
                printf("1. Iniciar sesión\n");
                printf("2. Registrarse\n");
                printf("0. Volver atras\n");
                printf("-------------------------------------\n");
                printf("\nElija una opción: ");
                scanf("%d", &opcion_cliente);

                system("cls");

                switch (opcion_cliente)
                {
                case 1:
                    iniciarSesion(); /// usuario.c
                    break;

                case 2:
                {
                    stUsuario nuevo = registro_Usuario();
                    if (nuevo.dni != -1) /// se registró correctamente
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
                    printf("Opción no válida.\n");
                    break;
                }

                system("pause");
                system("cls");

            }
                while (opcion_cliente != 0);
        }
        break;

        case 0:
            printf("Volviendo al inicio...\n");
            break;

        default:
            printf("Opción no válida.\n");
            break;
        }


        system("pause");
        system("cls");


    }
    while (opcion_login != 0);
}
