#include <stdio.h>
#include <string.h>
#include "venta.h"
#include "fecha.h"
#include "auto_cliente.h"

#define ARCHIVO_AUTOS "autos.bin" /// lo vamos a usar

// FUNCION 1
Venta cargarVenta()
{
    Venta ventas;
    int existeCliente = 0;
    int existeAuto = 0;
    Cliente c;
    Auto a;

    printf("---- CARGA DE VENTA ----\n");

    printf("\nIngrese fecha de la venta:\n");
    cargar_Fecha(&ventas.fecha);

    do
    {
        printf("\nIngrese patente del auto vendido: ");
        scanf("%s", ventas.patenteAutoVendido);

        FILE *archA = fopen(ARCHIVO_AUTOS, "rb");
        if(archA != NULL)
        {
            existeAuto = 0;
            while(fread(&a, sizeof(Auto), 1, archA) == 1)
            {
                if(strcmp(a.patente, ventas.patenteAutoVendido) == 0)
                {
                    existeAuto = 1;
                    break;
                }
            }
            fclose(archA);
        }
        else
        {
            printf("\n❌ Error al abrir el archivo de autos.\n");
            break;
        }

        if(!existeAuto)
            printf("⚠ Auto no encontrado. Intente nuevamente.\n");

    } while(!existeAuto);

    printf("\nIngrese precio de venta: ");
    scanf("%f", &ventas.precioVenta);

    printf("Ingrese ganancia obtenida: ");
    scanf("%f", &ventas.ganancia);

    do
    {
        printf("\nIngrese DNI del comprador: ");
        scanf("%s", ventas.dniComprador);

        FILE *archC = fopen(ARCHIVO_CLIENTES, "rb");
        if(archC != NULL)
        {
            existeCliente = 0;
            while(fread(&c, sizeof(Cliente), 1, archC) == 1)
            {
                if(strcmp(c.dni, ventas.dniComprador) == 0)
                {
                    existeCliente = 1;
                    break;
                }
            }
            fclose(archC);
        }
        else
        {
            printf("\n❌ Error al abrir el archivo de clientes.\n");
            break;
        }

        if(!existeCliente)
            printf("⚠ Cliente no encontrado. Intente nuevamente.\n");

    } while(!existeCliente);

    printf("\nIngrese DNI del vendedor: ");
    scanf("%s", ventas.dniVendedor);

    return ventas;
}

// FUNCION 2
void registrarVenta()
{
    Venta ventas = cargarVenta();

    FILE *arch = fopen(ARCHIVO_VENTAS, "ab");
    if(arch != NULL)
    {
        if(fwrite(&ventas, sizeof(Venta), 1, arch) == 1)
            printf("\n✅ Venta registrada correctamente.\n");
        else
            printf("\n❌ Error al escribir la venta en el archivo.\n");

        fclose(arch);
    }
    else
        printf("\n❌ Error al abrir el archivo de ventas.\n");
}

// FUNCION 3
void mostrarVenta(Venta ventas)
{
    printf("-----------------------------------------\n");
    printf("Fecha: ");
    mostrar_Fecha(ventas.fecha);
    printf("Patente Auto Vendido: %s\n", ventas.patenteAutoVendido);
    printf("Precio Venta: $%.2f\n", ventas.precioVenta);
    printf("Ganancia: $%.2f\n", ventas.ganancia);
    printf("DNI Comprador: %s\n", ventas.dniComprador);
    printf("DNI Vendedor: %s\n", ventas.dniVendedor);
    printf("-----------------------------------------\n");
}

// FUNCION 4
void mostrarVentas()
{
    FILE *arch = fopen(ARCHIVO_VENTAS, "rb");
    if(arch != NULL)
    {
        Venta ventas;
        printf("\n==== LISTA DE VENTAS ====\n");
        while(fread(&ventas, sizeof(Venta), 1, arch) == 1)
        {
            mostrarVenta(ventas);
        }
        fclose(arch);
    }
    else
        printf("\nNo se pudo abrir el archivo de ventas.\n");
}
