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
#include "auto.h"
#include "reportes.h"

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
        printf("1. Gestion de Clientes (Agregar / Modificar)\n"); // <-- Etiqueta actualizada
        printf("2. Dato del auto del cliente (Cargar)\n");
        printf("3. Autos disponibles (Stock Empresa)\n");
        printf("4. Pagos (Vender Auto)\n");
        printf("5. Registrar empleado\n");
        printf("6. Eliminar empleado\n");
        printf("7. Cerrar Sesion (Volver al Login)\n");
        printf("8. Ventas (Ver historial)\n");
        printf("9. INGRESAR NUEVO AUTO (Cargar Stock)\n");
        printf("10. VER LISTA DE EMPLEADOS\n");
        printf("11. REPORTES\n");
        printf("0. Volver al inicio\n");
        printf("--------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1:
        {
            // --- SUB MENU PARA CUMPLIR REQUISITO 3B ---
            int op;
            printf("\n--- GESTION DE CLIENTES ---\n");
            printf("1. Cargar NUEVO Cliente\n");
            printf("2. MODIFICAR Cliente Existente\n");
            printf("Elija opcion: ");
            scanf("%d", &op);

            if (op == 1)
            {
                Cliente nuevoC = cargar_persona();
                guardar_cliente_en_archivo(nuevoC);
            }
            else if (op == 2)
            {
                modificar_cliente(); // Llamamos a la función que creamos
            }
            else
            {
                printf("Opcion invalida.\n");
            }
        }
        break;

        case 2:
            agregar_autos_cliente();
            break;
        case 3:
            mostrar_todos_autos_disponibles();
            break;
        case 4:
            gestionDePagos();
            break;
        case 5:
            agregar_empleado();
            break;
        case 6:
            eliminar_empleado();
            break;
        case 7:
            printf("Cerrando sesion...\n");
            return;
        case 8:
            printf("\n--- HISTORIAL DE VENTAS ---\n");
            mostrarVentas();
            break;
        case 9:
            agregar_auto_stock();
            break;
        case 10:
            printf("\n--- MOSTRANDO EMPLEADOS ---\n");
            mostrar_empleados();
            break;
        case 11:
            menu_reportes();
            break;
        case 0:
            printf("Volviendo al menu principal...\n");
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
// FUNCIONES AUXILIARES
//-----------------------------------------------------
stGerente cargar_un_empleado()
{
    stGerente nuevo;
    printf("---- REGISTRO DE NUEVO EMPLEADO ----\n");
    printf("Ingrese correo: \n");
    fflush(stdin);
    scanf("%s", nuevo.correo);
    printf("Ingrese contrasena: \n");
    fflush(stdin);
    scanf("%s", nuevo.contrasena);
    printf("Ingrese DNI: \n");
    scanf("%d", &nuevo.dni);
    printf("Ingrese dia de nacimiento: \n");
    scanf("%d", &nuevo.dia);
    printf("Ingrese mes de nacimiento: \n");
    scanf("%d", &nuevo.mes);
    printf("Ingrese anio de nacimiento: \n");
    scanf("%d", &nuevo.anios);
    printf("Ingrese rol (ej: vendedor, mecanico, administrador): \n");
    fflush(stdin);
    scanf("%s", nuevo.rol);
    return nuevo;
}

void agregar_empleado()
{
    FILE* file = fopen("empleados.bin", "ab");
    if (file == NULL)
    {
        printf("Error al abrir archivo empleados.\n");
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

void eliminar_empleado()
{
    FILE* file = fopen("empleados.bin", "rb");
    if (file == NULL)
    {
        printf("No hay empleados.\n");
        return;
    }

    stGerente lista[50]; // máximo 50 empleados
    int cant = 0;
    stGerente emple;

    // Leer todos los empleados
    while (fread(&emple, sizeof(stGerente), 1, file))
    {
        lista[cant++] = emple;
    }

    fclose(file);

    int buscar_dni;
    printf("Ingrese el DNI del empleado a eliminar: ");
    scanf("%d", &buscar_dni);

    int encontrado = 0;
    for (int i = 0; i < cant; i++)
    {
        if (lista[i].dni == buscar_dni)
        {
            encontrado = 1;
            // Mover todos los posteriores una posición atrás
            for (int j = i; j < cant-1; j++)
                lista[j] = lista[j+1];
            cant--;
            break;
        }
    }

    if (encontrado == 0)
    {
        printf("No se encontro el empleado.\n");
        return;
    }

    // Volver a escribir el archivo
    file = fopen("empleados.bin", "wb");
    for (int i = 0; i < cant; i++)
    {
        fwrite(&lista[i], sizeof(stGerente), 1, file);
    }

    fclose(file);
    printf("Empleado eliminado correctamente.\n");
}

void mostrar_empleados()
{
    FILE* file = fopen("empleados.bin", "rb");
    if (file == NULL)
    {
        printf("No hay empleados registrados aun.\n");
        return;
    }

    stGerente emple;
    int contador = 0;

    printf("\n-------- LISTA DE EMPLEADOS --------\n");
    printf("------------------------------------\n");

    while (fread(&emple, sizeof(stGerente), 1, file) == 1)
    {
        printf("Empleado #%d\n", contador++);
        printf("DNI: %d\n", emple.dni);
        printf("Correo: %s\n", emple.correo);
        printf("Rol: %s\n", emple.rol);
        printf("------------------------------------\n");
    }
    fclose(file);
}
