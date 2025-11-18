#include <stdio.h>
#include <stdlib.h>
#include "autos_disponibles.h"
#include "auto.h" // <--- IMPORTANTE: Aquí está la estructura 'Auto' real

void mostrar_todos_autos_disponibles()
{
    // Abrimos el MISMO archivo donde escribe el Gerente/Admin
    // Asegurate que en auto.h esté definido ARCHIVO_AUTOS como "autos.bin"
    FILE *file = fopen("autos.bin", "rb");

    if(file == NULL)
    {
        printf("\n[!] No hay autos disponibles en stock por el momento.\n");
        printf("    (El gerente debe cargar autos primero).\n");
        return;
    }

    Auto a; // Usamos la estructura real de la empresa
    int hayAutos = 0;

    printf("\n==========================================================\n");
    printf("               AUTOS DISPONIBLES (Stock Real)             \n");
    printf("==========================================================\n");
    printf("PATENTE      | MARCA        | MODELO       | PRECIO       \n");
    printf("----------------------------------------------------------\n");

    // Leemos el archivo registro por registro
    while(fread(&a, sizeof(Auto), 1, file) == 1)
    {
        // Asumimos que si tiene patente valida, el auto es valido
        printf("%-12s | %-12s | %-12s | $%.2f\n",
               a.patente,
               a.marca,
               a.modelo,
               a.precioFinal); // O precioDeAdquisicion, segun tu logica
        hayAutos = 1;
    }

    if(!hayAutos)
    {
        printf("\n   El archivo existe pero esta vacio.\n");
    }

    printf("==========================================================\n");
    printf("NOTA: Copie la PATENTE exacta para proceder a la compra.\n");

    fclose(file);
}
