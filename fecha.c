#include <stdio.h>
#include <string.h>
#include "fecha.h"

/// FUNCION 1
void cargar_Fecha()
{
    Fecha f;
    printf("\n(dd/mm/aaaa): ");
    scanf("%d %d %d", &f.dia, &f.mes, &f.anio);
}

/// FUNCION 2
void mostrar_Fecha(Fecha f)
{
    printf("%d/%d/%d\n", f.dia, f.mes, f.anio);
}
