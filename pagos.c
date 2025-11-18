#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagos.h"
#include "auto.h"

// --- FUNCION NUEVA: Eliminar auto del archivo fisico ---
void eliminar_auto_stock(char patenteEliminar[])
{
    FILE *archivo = fopen("autos.bin", "rb");
    FILE *temporal = fopen("temp.bin", "wb");

    if (archivo == NULL || temporal == NULL)
    {
        printf("Error al intentar actualizar el stock.\n");
        return;
    }

    Auto a;
    int encontrado = 0;

    // Copiamos todos los autos EXCEPTO el que tiene la patente vendida
    while(fread(&a, sizeof(Auto), 1, archivo) == 1)
    {
        if(strcmp(a.patente, patenteEliminar) != 0)
        {
            // Si NO es la patente que busco, lo guardo en el nuevo archivo
            fwrite(&a, sizeof(Auto), 1, temporal);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(archivo);
    fclose(temporal);

    if(encontrado)
    {
        // Borramos el viejo y renombramos el nuevo
        remove("autos.bin");
        rename("temp.bin", "autos.bin");
        printf("\n[SISTEMA] El auto se ha quitado de la lista de disponibles.\n");
    }
    else
    {
        // Si no pasó nada, borramos el temporal
        remove("temp.bin");
    }
}

// --- FUNCIONES AUXILIARES DE SIEMPRE ---

void ordenarPorPatente(Auto autos[], int validos)
{
    Auto aux;
    int i, j;
    for(i = 0; i < validos - 1; i++)
    {
        for(j = i + 1; j < validos; j++)
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

int buscarPatenteBinaria(Auto autos[], int validos, char patenteBuscada[])
{
    int inicio = 0;
    int fin = validos - 1;

    while (inicio <= fin)
    {
        int medio = inicio + (fin - inicio) / 2;
        int comparacion = strcmp(autos[medio].patente, patenteBuscada);

        if (comparacion == 0) return medio;
        if (comparacion < 0) inicio = medio + 1;
        else fin = medio - 1;
    }
    return -1;
}

// --- GESTION DE PAGOS (Actualizada) ---

void gestionDePagos()
{
    FILE *file = fopen("autos.bin", "rb");
    if(file == NULL)
    {
        printf("\nError: No hay autos cargados por el administrador.\n");
        return;
    }

    Auto listaAutos[100];
    int validos = 0;

    // Cargamos autos en memoria para buscar rapido
    while(fread(&listaAutos[validos], sizeof(Auto), 1, file) == 1 && validos < 100)
    {
        validos++;
    }
    fclose(file);

    if(validos == 0)
    {
        printf("El stock de autos esta vacio.\n");
        return;
    }

    ordenarPorPatente(listaAutos, validos);

    char patenteBusq[11];
    printf("\n--- BUSQUEDA DE AUTO PARA PAGO ---\n");
    printf("Ingrese la patente del auto que desea comprar: ");
    scanf("%s", patenteBusq);

    int pos = buscarPatenteBinaria(listaAutos, validos, patenteBusq);

    if(pos != -1)
    {
        printf("\n----------------------------------\n");
        printf("AUTO ENCONTRADO:\n");
        printf("Marca: %s - Modelo: %s\n", listaAutos[pos].marca, listaAutos[pos].modelo);
        printf("Precio: $%.2f\n", listaAutos[pos].precioFinal);
        printf("----------------------------------\n");

        char confirmacion;
        printf("\nLo desea comprar SI o NO? (s/n): ");
        fflush(stdin);
        scanf(" %c", &confirmacion);

        if(confirmacion == 's' || confirmacion == 'S')
        {
            printf("\n********************************\n");
            printf("   FELICIDADES, LO COMPRASTE!   \n");
            printf("********************************\n");

            // AQUI ESTA EL CAMBIO: Llamamos a la funcion para borrarlo
            eliminar_auto_stock(patenteBusq);

            // Opcional: Pausa para leer
            system("pause");
        }
        else
        {
            printf("\nNO PASA NADA. Operacion cancelada.\n");
        }
    }
    else
    {
        printf("\n[!] El auto con patente %s no fue encontrado.\n", patenteBusq);
        printf("NO PASA NADA.\n");
    }
}
