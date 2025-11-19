#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagos.h"
#include "auto.h"
#include "auto_cliente.h"
#include "venta.h"
#include "fecha.h"

// --- FUNCION AUXILIAR: Transferir Auto a Cliente ---
void transferir_auto_a_cliente(Auto autoVendido, char dniComprador[])
{
    FILE *file = fopen("autos_cliente.bin", "ab");
    if(file == NULL) return;

    AutoCliente autoNuevo;

    strcpy(autoNuevo.patente, autoVendido.patente);
    strcpy(autoNuevo.marca, autoVendido.marca);
    strcpy(autoNuevo.modelo, autoVendido.modelo);
    autoNuevo.anio = autoVendido.anio;
    autoNuevo.kms = autoVendido.kms;
    autoNuevo.precioDeAdquisicion = autoVendido.precioDeAdquisicion;
    autoNuevo.precioFinal = autoVendido.precioFinal;

    strcpy(autoNuevo.titular.dni, dniComprador);
    strcpy(autoNuevo.titular.nombre, "Propietario (Venta)");
    strcpy(autoNuevo.titular.rol, "comprador");

    fwrite(&autoNuevo, sizeof(AutoCliente), 1, file);
    fclose(file);
    printf("\n[SISTEMA] Transferencia de propiedad registrada.\n");
}

// --- FUNCION: Eliminar auto del stock ---
void eliminar_auto_stock(char patenteEliminar[])
{
    FILE *archivo = fopen("autos.bin", "rb");
    if (archivo == NULL)
    {
        printf("No hay autos en stock.\n");
        return;
    }

    Auto lista[50]; // máximo 50 autos
    int cant = 0;
    Auto a;

    // Leer todos los autos
    while (fread(&a, sizeof(Auto), 1, archivo))
    {
        lista[cant++] = a;
    }

    fclose(archivo);

    int encontrado = 0;
    for (int i = 0; i < cant; i++)
    {
        if (strcmp(lista[i].patente, patenteEliminar) == 0)
        {
            encontrado = 1;
            // Mover los posteriores una posición atrás
            for (int j = i; j < cant-1; j++)
                lista[j] = lista[j+1];
            cant--;
            break;
        }
    }

    if (encontrado == 0)
    {
        printf("No se encontró el auto.\n");
        return;
    }

    // Reescribir el archivo con los autos restantes
    archivo = fopen("autos.bin", "wb");
    for (int i = 0; i < cant; i++)
    {
        fwrite(&lista[i], sizeof(Auto), 1, archivo);
    }

    fclose(archivo);
    printf("Auto eliminado del stock.\n");
}

// --- FUNCION: Registrar venta en archivo ---
void registrar_venta_archivo(Auto autoVendido, char dniComprador[], char dniVendedor[])
{
    FILE *file = fopen("ventas.bin", "ab");
    if(file == NULL)
    {
        printf("No se pudo registrar la venta.\n");
        return;
    }

    Venta nuevaVenta;

    printf("\nIngrese la fecha de la venta:\n");
    nuevaVenta.fecha = cargar_Fecha();

    strcpy(nuevaVenta.patenteAutoVendido, autoVendido.patente);
    nuevaVenta.precioVenta = autoVendido.precioFinal;
    nuevaVenta.ganancia = autoVendido.precioFinal - autoVendido.precioDeAdquisicion;
    strcpy(nuevaVenta.dniComprador, dniComprador);
    strcpy(nuevaVenta.dniVendedor, dniVendedor);

    fwrite(&nuevaVenta, sizeof(Venta), 1, file);
    fclose(file);

    printf("\nVenta registrada exitosamente.\n");
    printf("Ganancia obtenida: $%.2f\n", nuevaVenta.ganancia); /// ver si esto sirve
}

// --- ORDENAMIENTO ---
void ordenarPorPatente(Auto autos[], int validos)
{
    Auto aux;
    for(int i = 0; i < validos - 1; i++)
    {
        for(int j = i + 1; j < validos; j++)
        {
            if(strcmp(autos[i].patente, autos[j].patente) > 0)
            {
                aux = autos[i];
                autos[i] = autos[j];
                autos[j] = aux;
            }
        }
    }
}

// --- BUSQUEDA BINARIA ---
int buscarPatenteBinaria(Auto autos[], int validos, char patenteBuscada[])
{
    int inicio = 0;
    int fin = validos - 1;

    while(inicio <= fin)
    {
        int medio = inicio + (fin - inicio) / 2;
        int comparacion = strcmp(autos[medio].patente, patenteBuscada);

        if(comparacion == 0)
        {
            return medio;
        }
        if(comparacion < 0)
        {
            inicio = medio + 1;
        }
        else
        {
            fin = medio - 1;
        }
    }
    return -1;
}

// --- GESTION DE PAGOS PRINCIPAL ---
void gestionDePagos()
{
    FILE *file = fopen("autos.bin", "rb");
    if(file == NULL)
    {
        printf("\nError: No hay stock disponible.\n");
        return;
    }

    Auto listaAutos[100];
    int validos = 0;

    /// esto quiere decir que mientras el fread valga 1 seria el archivo tengo informacion y validos sea menor que 100 que entre al while
    while(fread(&listaAutos[validos], sizeof(Auto), 1, file) == 1 && validos < 100)
    {
        validos++;
    }
    fclose(file);

    if(validos == 0)
    {
        printf("El stock está vacío.\n");
        return;
    }

    ordenarPorPatente(listaAutos, validos);

    char patenteBusq[11];
    printf("\n--- VENTA DE UNIDAD ---\n");
    printf("Ingrese patente del auto: ");
    scanf("%s", patenteBusq);

    int pos = buscarPatenteBinaria(listaAutos, validos, patenteBusq);

    if(pos != -1)
    {
        printf("\n--- AUTO SELECCIONADO ---\n");
        printf("Modelo: %s %s\n", listaAutos[pos].marca, listaAutos[pos].modelo);
        printf("Precio: $%.2f\n", listaAutos[pos].precioFinal);
        printf("Ganancia estimada: $%.2f\n",
               listaAutos[pos].precioFinal - listaAutos[pos].precioDeAdquisicion);

        char confirmacion;
        printf("\n¿Confirmar venta? (s/n): ");
        fflush(stdin);
        scanf(" %c", &confirmacion);

        if(confirmacion == 's' || confirmacion == 'S')
        {
            char dniComprador[15];
            char dniVendedor[15];

            printf("\nDNI del Comprador: ");
            scanf("%s", dniComprador);

            printf("DNI del Vendedor: ");
            scanf("%s", dniVendedor);

            registrar_venta_archivo(listaAutos[pos], dniComprador, dniVendedor);
            transferir_auto_a_cliente(listaAutos[pos], dniComprador);
            eliminar_auto_stock(patenteBusq);

            printf("\n********************************\n");
            printf("  ¡VENTA COMPLETADA CON ÉXITO!  \n");
            printf("********************************\n");
        }
        else
        {
            printf("\nOperación cancelada.\n");
        }
    }
    else
    {
        printf("\n Auto no encontrado en stock.\n");
    }
}
