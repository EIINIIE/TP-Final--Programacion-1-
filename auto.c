#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auto.h"
#include "persona.h"

// FUNCION 1
Auto cargar_auto()
{
    Auto autos;

    printf("----DATOS DEL AUTO----\n");
    printf("Patente: ");
    scanf("%s", autos.patente);
    printf("Marca: ");
    scanf("%s", autos.marca);
    printf("Modelo: ");
    scanf("%s", autos.modelo);
    printf("Año: ");
    scanf("%d", &autos.anio);
    printf("Kilometros: ");
    scanf("%d", &autos.kms);
    printf("Precio: ");
    scanf("%f", &autos.precioDeAdquisicion);

autos.precioFinal = medioDPago(autos.precioDeAdquisicion);

    printf("Precio original: $%.2f\n", autos.precioDeAdquisicion);
    printf("Precio final: $%.2f\n", autos.precioFinal);

    return autos;
}

// FUNCION 2
void agregar_autos()
{
    FILE* file = fopen(ARCHIVO_AUTOS, "ab");
    if(file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    Auto nuevo_auto = cargar_auto();
    nuevo_auto.titular = cargar_persona();  // Usamos persona

    fwrite(&nuevo_auto, sizeof(Auto), 1, file);
    fclose(file);
    printf("Auto y titular cargados correctamente\n");
}

// FUNCION 3
void mostrar_auto(Auto autos)
{
    printf("---- DATOS DEL VEHICULO ----\n");
    printf("Patente: %s\n", autos.patente);
    printf("Marca: %s\n", autos.marca);
    printf("Modelo: %s\n", autos.modelo);
    printf("Año: %d\n", autos.anio);
    printf("Kilometraje: %d\n", autos.kms);
    printf("Precio de adquisición: $%.2f\n", autos.precioDeAdquisicion);
    printf("Precio final: $%.2f\n", autos.precioFinal);

    printf("\n---- DATOS DEL TITULAR ----\n");
    printf("DNI: %d\n", autos.titular.dni);
    printf("Nombre: %s\n", autos.titular.nombre);
    printf("Teléfono: %s\n", autos.titular.telefono);
    printf("Dirección: %s\n", autos.titular.direccion);
    printf("Rol: %s\n", autos.titular.rol);
}

// FUNCION 4
void mostrar_todos_autos(char archivo[])
{
    FILE* file = fopen(archivo, "rb");
    if(file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    Auto a;
    while(fread(&a, sizeof(Auto), 1, file) == 1)
    {
        mostrar_auto(a); // muestra un auto con sus datos
        printf("\n");
    }
    fclose(file);
}

//FUNCION 5
float medioDPago(float precioDeAdquisicion)
{
    int porcentajeEfectivo = 20 + rand() % 21;   // 20 a 40%
    int porcentajeEnTarjeta = 5 + rand() % 16;   // 5 a 20%
    int medio;
    float precioFinal = precioDeAdquisicion; ///
    float resultado = 0; // <- para guardar el monto del descuento o recargo ///

    printf("\n--- MEDIO DE PAGO ---\n");
    printf("1_ Si pagas en efectivo te damos un %d%% de descuento\n", porcentajeEfectivo);
    printf("2_ Si pagas con tarjeta te damos un recargo de %d%%\n", porcentajeEnTarjeta);
    printf("Ingrese el medio de pago: ");
    scanf("%d", &medio);

    if(medio == 1)
    {
        resultado = (precioDeAdquisicion * porcentajeEfectivo) / 100.0; ///
        precioFinal = precioDeAdquisicion - resultado; ///
        printf("\nDescuento aplicado: $%.2f\n", resultado); ///
    }
    else if(medio == 2)
    {
        resultado = (precioDeAdquisicion * porcentajeEnTarjeta) / 100.0; ///
        precioFinal = precioDeAdquisicion + resultado; ///
        printf("\nRecargo aplicado: $%.2f\n", resultado); ///
    }
    else
    {
        printf("Opcion no valida, se mantiene el precio original.\n");
    }

    printf("Precio final: $%.2f\n", precioFinal); ///

    return precioFinal;
}

//FUNCION 6

