#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auto.h"
#include "cliente.h"
#include "pagos.h" // Necesario si usas medioDPago aqui

// FUNCION 1: Cargar datos de un auto (Generico)
Auto cargar_auto()
{
    Auto autos;
    // Inicializamos titular vacio por defecto
    strcpy(autos.titular.nombre, "SIN ASIGNAR");

    printf("---- DATOS DEL AUTO ----\n");
    printf("Patente: ");
    scanf("%s", autos.patente);
    printf("Marca: ");
    scanf("%s", autos.marca);
    printf("Modelo: ");
    scanf("%s", autos.modelo);
    printf("Anio: ");
    scanf("%d", &autos.anio);
    printf("Kilometros: ");
    scanf("%d", &autos.kms);
    printf("Precio: ");
    scanf("%f", &autos.precioDeAdquisicion);

    autos.precioFinal = autos.precioDeAdquisicion;

    return autos;
}

// FUNCION 2: Agregar auto (Usada por clientes externos)
void agregar_autos()
{
    FILE* file = fopen(ARCHIVO_AUTOS, "ab");
    if(file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    Auto nuevo_auto = cargar_auto();
    nuevo_auto.titular = cargar_persona();  // Aqui si pedimos titular

    fwrite(&nuevo_auto, sizeof(Auto), 1, file);
    fclose(file);
    printf("Auto cargado correctamente\n");
}

// FUNCION 3: Mostrar un auto
void mostrar_auto(Auto a)
{
    printf("Patente: %-10s | Marca: %-10s | Modelo: %-10s | Precio: $%.2f\n",
           a.patente, a.marca, a.modelo, a.precioFinal);
}

// FUNCION 4: Mostrar todos (Para Autos Disponibles)
void mostrar_todos_autos(char archivo[])
{
    FILE* file = fopen(archivo, "rb");
    if(file == NULL)
    {
        printf("Error al abrir el archivo de autos.\n");
        return;
    }

    Auto a;
    printf("\nLISTADO DE AUTOS:\n");
    while(fread(&a, sizeof(Auto), 1, file) == 1)
    {
        mostrar_auto(a);
    }
    fclose(file);
}

// FUNCION 5: Medio de pago (Logica simple)
float medioDPago(float precioDeAdquisicion)
{
    // Puedes reutilizar la logica de pagos.c o dejarla simple aqui
    return precioDeAdquisicion;
}

// ------------------------------------------------------------
// NUEVA FUNCION: Permite al Gerente cargar stock manual
// ------------------------------------------------------------
void agregar_auto_stock()
{
    FILE *file = fopen(ARCHIVO_AUTOS, "ab"); // "ab" para agregar al final
    if(file == NULL)
    {
        printf("Error al abrir el archivo de stock (autos.bin).\n");
        return;
    }

    Auto nuevo;

    printf("\n--- INGRESO DE NUEVO AUTO AL STOCK (GERENCIA) ---\n");

    printf("Patente: ");
    scanf("%s", nuevo.patente);

    printf("Marca: ");
    scanf("%s", nuevo.marca);

    printf("Modelo: ");
    scanf("%s", nuevo.modelo);

    printf("Anio: ");
    scanf("%d", &nuevo.anio);

    printf("Kilometros: ");
    scanf("%d", &nuevo.kms);

    printf("Precio de Venta (Base): $");
    scanf("%f", &nuevo.precioDeAdquisicion);

    // Configuración automática para stock
    nuevo.precioFinal = nuevo.precioDeAdquisicion;
    strcpy(nuevo.titular.nombre, "CONCESIONARIA"); // Dueño empresa
    strcpy(nuevo.titular.dni, "000");
    nuevo.titular.rol[0] = '\0';

    fwrite(&nuevo, sizeof(Auto), 1, file);
    fclose(file);

    printf("\n[OK] Auto patente %s agregado al stock correctamente.\n", nuevo.patente);
}
