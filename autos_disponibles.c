#include <stdio.h>
#include "autos_disponibles.h"

// Autos pre-cargados
stAuto autos[MAX_AUTOS] =
{
    {1, "Toyota", "Corolla", 2020, 15000},
    {2, "Honda", "Civic", 2019, 14000},
    {3, "Ford", "Focus", 2021, 16000},
    {4, "Chevrolet", "Cruze", 2018, 13000},
    {5, "Volkswagen", "Golf", 2022, 20000},
};

int cantidad_autos = 5;

// Función para mostrar los autos
void mostrar_todos_autos_disponibles()
{
    printf("\n--- AUTOS DISPONIBLES ---\n");
    for(int i = 0; i < cantidad_autos; i++)
    {
        printf("ID: %d - %s %s %d - $%.2f\n",
               autos[i].id,
               autos[i].marca,
               autos[i].modelo,
               autos[i].anio,
               autos[i].precio);
    }
}
