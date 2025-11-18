


#include <stdio.h>
#include <stdlib.h>
#include "pagos.h"

float medioDPago(float precioDeAdquisicion)
{
    // Eliminamos el srand aquí si ya está en el main.c, sino se repiten números
    int porcentajeEfectivo = 20 + rand() % 21;   // 20 a 40%
    int porcentajeEnTarjeta = 5 + rand() % 16;   // 5 a 20%
    int medio;
    float precioFinal = precioDeAdquisicion;
    float resultado = 0;

    printf("\n--- MEDIO DE PAGO ---\n");
    printf("1_ Efectivo (Descuento del %d%%)\n", porcentajeEfectivo);
    printf("2_ Tarjeta (Recargo del %d%%)\n", porcentajeEnTarjeta);
    printf("Ingrese el medio de pago: ");
    scanf("%d", &medio);

    if(medio == 1)
    {
        resultado = (precioDeAdquisicion * porcentajeEfectivo) / 100.0;
        precioFinal = precioDeAdquisicion - resultado;
        printf("Descuento aplicado: $%.2f\n", resultado);
    }
    else if(medio == 2)
    {
        resultado = (precioDeAdquisicion * porcentajeEnTarjeta) / 100.0;
        precioFinal = precioDeAdquisicion + resultado;
        printf("Recargo aplicado: $%.2f\n", resultado);
    }
    else
    {
        printf("Opcion no valida, se mantiene el precio original.\n");
    }

    printf("Precio final: $%.2f\n", precioFinal);

    return precioFinal;
}



/*
///---------------------------------------------------------------------------------------------------------------------

/// esta funcion va en el archivo de pagos ( hay q agregar un archivo de paogs.c y.h para esta funcion )


///FUNCION 5
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
    }
    else if(medio == 2)
    {
        resultado = (precioDeAdquisicion * porcentajeEnTarjeta) / 100.0; ///
        precioFinal = precioDeAdquisicion + resultado; ///
    }
    else
    {
        printf("Opcion no valida, se mantiene el precio original.\n");
    }

    printf("Precio final: $%.2f\n", precioFinal); ///

    return precioFinal;
}

*/
