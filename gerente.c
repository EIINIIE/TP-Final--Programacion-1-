#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gerente.h"
#include "empleado.h"
#include "cliente.h"
#include "auto_cliente.h"
#include "autos_disponibles.h"
#include "pagos.h"
#include "venta.h"
#include "auto.h" // <--- AGREGADO: Necesario para usar agregar_auto_stock()

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

    printf("Ingrese su contrasenia: ");
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

//-----------------------------------------------------
// FUNCION 2 - Menu Completo del Gerente
//-----------------------------------------------------
void menu_gerente()
{
    int opcion;

    do
    {
        printf("\n==================================================\n");
        printf("       SESION INICIADA: ADMINISTRADOR (GERENTE)     \n");
        printf("==================================================\n");
        printf("1. Datos del cliente (Cargar nuevo)\n");
        printf("2. Dato del auto del cliente (Cargar)\n");
        printf("3. Autos disponibles (Stock Empresa)\n");
        printf("4. Pagos (Vender Auto)\n");
        printf("5. Registrar empleado\n");
        printf("6. Dar de baja al empleado\n");
        printf("7. Volver al inicio (Cerrar Sesion)\n");
        printf("8. Ventas (Ver historial)\n");
        printf("9. INGRESAR NUEVO AUTO (Cargar Stock)\n"); // <--- AGREGADO
        printf("0. Salir del sistema\n");
        printf("--------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1: // Funcionalidad compartida con empleado
            printf("\n--- GESTION DE CLIENTES ---\n");
            cargar_persona();
            break;

        case 2: // Funcionalidad compartida
            printf("\n--- CARGA DE AUTO DE CLIENTE ---\n");
            agregar_autos_cliente();
            break;

        case 3: // Ver stock real
            mostrar_todos_autos_disponibles();
            break;

        case 4: // Realizar una venta/pago
            gestionDePagos();
            break;

        case 5: // Exclusivo Gerente
            agregar_empleado();
            break;

        case 6: // Exclusivo Gerente
            eliminar_empleado();
            break;

        case 7:
            printf("Cerrando sesion y volviendo al menu principal...\n");
            return; // Vuelve al main()

        case 8: // Exclusivo Gerente (Reportes)
            printf("\n--- HISTORIAL DE VENTAS ---\n");
            mostrarVentas();
            break;

        case 9: // <--- AGREGADO: Llamada a la funcion nueva
            agregar_auto_stock();
            break;

        case 0:
            printf("Saliendo del sistema completamente...\n");
            exit(0); // Cierra el programa
            break;

        default:
            printf("Opcion invalida. Intente nuevamente.\n");
            break;
        }

        if (opcion != 7 && opcion != 0)
        {
            system("pause");
            system("cls");
        }

    }
    while (opcion != 7 && opcion != 0);
}

//-----------------------------------------------------
// FUNCION 3 - Cargar un empleado nuevo (Interna)
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
    FILE* file = fopen("empleados.bin", "ab");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de empleados.\n");
        return;
    }

    char control = 's';
    while (control == 's' || control == 'S')
    {
        stGerente nuevo = cargar_un_empleado();
        fwrite(&nuevo, sizeof(stGerente), 1, file);

        printf("Empleado registrado con exito.\n");
        printf("Desea registrar otro empleado? (s/n): ");
        fflush(stdin);
        scanf(" %c", &control);
    }

    fclose(file);
}

//-----------------------------------------------------
// FUNCION 5 - Eliminar empleado por DNI
//-----------------------------------------------------
void eliminar_empleado()
{
    FILE* file = fopen("empleados.bin", "rb");
    if (file == NULL)
    {
        printf("No hay empleados registrados o no se pudo abrir el archivo.\n");
        return;
    }

    // Usamos archivo temporal para la baja fisica
    FILE* temp = fopen("temp_empleados.bin", "wb");
    if (temp == NULL)
    {
        fclose(file);
        printf("Error creando archivo temporal.\n");
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
            printf("Esta seguro de eliminarlo? (s/n): ");
            char confirmar;
            fflush(stdin);
            scanf(" %c", &confirmar);

            if (confirmar == 's' || confirmar == 'S')
            {
                printf("Empleado eliminado.\n");
                // NO lo escribimos en el temporal -> Se borra
            }
            else
            {
                // Si se arrepiente, lo escribimos
                fwrite(&emple, sizeof(stGerente), 1, temp);
                printf("Eliminacion cancelada.\n");
            }
        }
        else
        {
            // Si no es el buscado, lo copiamos al temporal
            fwrite(&emple, sizeof(stGerente), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado)
    {
        remove("empleados.bin");
        rename("temp_empleados.bin", "empleados.bin");
    }
    else
    {
        remove("temp_empleados.bin");
        printf("No se encontro un empleado con ese DNI.\n");
    }
}

//-----------------------------------------------------
// FUNCION 6 - Mostrar empleados cargados (Auxiliar)
//-----------------------------------------------------
void mostrar_empleados()
{
    FILE* file = fopen("empleados.bin", "rb");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo de empleados.\n");
        return;
    }

    stGerente emple;
    int contador = 0;

    printf("-------- LISTA DE EMPLEADOS --------\n");

    while (fread(&emple, sizeof(stGerente), 1, file) == 1)
    {
        printf("Empleado #%d\n", ++contador);
        printf("DNI: %d\n", emple.dni);
        printf("Correo: %s\n", emple.correo);
        printf("Rol: %s\n", emple.rol);
        printf("------------------------------------\n");
    }

    fclose(file);
}
