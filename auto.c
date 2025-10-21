#include <stdio.h>
#include <stdlib.h>
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

 autos.precioDeAdquisicion = medioDPago(autos.precioDeAdquisicion);

    printf("Precio original: $%d\n", autos.precioDeAdquisicion);
    printf("Precio final: $%d\n", autos.precioFinal);

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
void mostrar_auto(Auto a)
{
    printf("----DATOS DEL VEHICULO----\n");
    printf("Patente: %s\n", a.patente);
    printf("Marca: %s\n", a.marca);
    printf("Modelo: %s\n", a.modelo);
    printf("Año: %d\n", a.anio);
    printf("Kilometraje: %d\n", a.kms);
    printf("Precio de adquisición: $%.2f\n", a.precioDeAdquisicion);

    printf("----DATOS DEL TITULAR----\n");
    printf("DNI: %s\n", a.titular.dni);
    printf("Nombre: %s\n", a.titular.nombre);
    printf("Teléfono: %s\n", a.titular.telefono);
    printf("Dirección: %s\n", a.titular.direccion);
    printf("Rol: %s\n", a.titular.rol);
}

// FUNCION 4
void mostrar_autos(char archivo[])
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
        mostrar_auto(a);
        printf("\n");
    }
    fclose(file);
}

//FUNCION 5
int medioDPago(int precioDeAdquisicion)
{
    int porcentajeEfectivo = 20 + rand() % 21;   // 20 a 40%
    int porcentajeEnTarjeta = 5 + rand() % 16;   // 5 a 20%
    int medio;
    int precioFinal = precioDeAdquisicion;
    float diferencia = 0; // <- para guardar el monto del descuento o recargo

    printf("\n--- MEDIO DE PAGO ---\n");
    printf("1_ Si pagas en efectivo te damos un %d%% de descuento\n", porcentajeEfectivo);
    printf("2_ Si pagas con tarjeta te damos un recargo de %d%%\n", porcentajeEnTarjeta);
    printf("Ingrese el medio de pago: ");
    scanf("%d", &medio);

    if(medio == 1)
    {
        diferencia = (precioDeAdquisicion * porcentajeEfectivo) / 100.0;
        precioFinal = precioDeAdquisicion - diferencia;
        printf("\nDescuento aplicado: $%.2f\n", diferencia);
    }
    else if(medio == 2)
    {
        diferencia = (precioDeAdquisicion * porcentajeEnTarjeta) / 100.0;
        precioFinal = precioDeAdquisicion + diferencia;
        printf("\nRecargo aplicado: $%.2f\n", diferencia);
    }
    else
    {
        printf("Opcion no valida, se mantiene el precio original.\n");
    }

    printf("Precio final: $%d\n", precioFinal);

    return precioFinal;
}

//FUNCION 6
Auto modificar_auto(Auto autos)
{
    int opcion;
    srand(time(NULL));

    do
    {
        printf("\n--- MODIFICAR AUTO ---\n");
        printf("1_ Modificar marca\n");
        printf("2_ Modificar modelo\n");
        printf("3_ Modificar precio de adquisicion\n");
        printf("4_ Modificar medio de pago (recalcula precio final)\n");
        printf("0_ Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            printf("Ingrese nueva marca: ");
            fflush(stdin);
            gets(autos.marca);
            printf("Marca modificada con exito.\n");
            break;

        case 2:
            printf("Ingrese nuevo modelo: ");
            fflush(stdin);
            gets(autos.modelo);
            printf("Modelo modificado con exito.\n");
            break;

        case 3:
            printf("Ingrese nuevo precio de adquisicion: ");
            scanf("%d", &autos.precioDeAdquisicion);
            printf("Precio de adquisicion modificado.\n");
            break;

        case 4:
            autos.precioFinal = medioDPago(autos.precioDeAdquisicion);
            printf("Medio de pago actualizado. Nuevo precio final: $%d\n", autos.precioFinal);
            break;

        case 0:
            printf("Saliendo del menu de modificacion...\n");
            break;

        default:
            printf("Opcion invalida.\n");
            break;
        }

    } while(opcion != 0);

    return autos;
}
