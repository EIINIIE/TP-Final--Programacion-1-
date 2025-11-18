#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagos.h"
#include "auto.h" // Necesitamos la estructura Auto
#include "auto_cliente.h" // Y la definición de ARCHIVO_AUTOS

// --- FUNCIONES AUXILIARES (INTERNAS) ---

// 1. Función para ordenar el arreglo (NECESARIO para Búsqueda Binaria)
void ordenarPorPatente(Auto autos[], int validos)
{
    Auto aux;
    int i, j;
    for(i = 0; i < validos - 1; i++)
    {
        for(j = i + 1; j < validos; j++)
        {
            // Si la patente 'i' es mayor que la 'j', intercambiamos
            if(strcmp(autos[i].patente, autos[j].patente) > 0)
            {
                aux = autos[i];
                autos[i] = autos[j];
                autos[j] = aux;
            }
        }
    }
}

// 2. Algoritmo de Búsqueda Binaria
int buscarPatenteBinaria(Auto autos[], int validos, char patenteBuscada[])
{
    int inicio = 0;
    int fin = validos - 1;

    while (inicio <= fin)
    {
        int medio = inicio + (fin - inicio) / 2;
        int comparacion = strcmp(autos[medio].patente, patenteBuscada);

        if (comparacion == 0)
        {
            return medio; // Encontrado, retorna la posición
        }
        if (comparacion < 0)
        {
            inicio = medio + 1; // Buscar en la mitad derecha
        }
        else
        {
            fin = medio - 1; // Buscar en la mitad izquierda
        }
    }
    return -1; // No encontrado
}

// --- FUNCION PRINCIPAL DEL MODULO ---

void gestionDePagos()
{
    FILE *file = fopen(ARCHIVO_AUTOS, "rb");
    if(file == NULL)
    {
        printf("\nError: No se encuentra el archivo de autos para buscar.\n");
        return;
    }

    // 1. Cargar archivo en memoria
    Auto listaAutos[100]; // Suponemos un maximo de 100 para este ejemplo
    int validos = 0;

    while(fread(&listaAutos[validos], sizeof(Auto), 1, file) == 1 && validos < 100)
    {
        validos++;
    }
    fclose(file);

    if(validos == 0)
    {
        printf("No hay autos cargados en el sistema.\n");
        return;
    }

    // 2. Ordenar el arreglo para poder usar busqueda binaria
    ordenarPorPatente(listaAutos, validos);

    // 3. Pedir patente al usuario
    char patenteBusq[11];
    printf("\n--- BUSQUEDA DE AUTO PARA PAGO ---\n");
    printf("Ingrese la patente del auto que desea comprar: ");
    scanf("%s", patenteBusq);

    // 4. Realizar Búsqueda Binaria
    int pos = buscarPatenteBinaria(listaAutos, validos, patenteBusq);

    // 5. Resultado y Confirmación
    if(pos != -1)
    {
        printf("\n----------------------------------\n");
        printf("AUTO ENCONTRADO:\n");
        printf("Marca: %s - Modelo: %s\n", listaAutos[pos].marca, listaAutos[pos].modelo);
        printf("Precio Base: $%.2f\n", listaAutos[pos].precioDeAdquisicion);
        printf("----------------------------------\n");

        char confirmacion;
        printf("\nLo desea comprar SI o NO? (s/n): ");
        fflush(stdin); // Limpiar buffer
        scanf(" %c", &confirmacion);

        if(confirmacion == 's' || confirmacion == 'S')
        {
            printf("\n********************************\n");
            printf("   FELICIDADES, LO COMPRASTE!   \n");
            printf("********************************\n");
            // Aca podrias guardar la venta en ventas.bin si quisieras
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

    system("pause");
}
