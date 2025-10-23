#include <stdio.h>
#include <string.h>
#include "fecha.h"


void cargar_Fecha()
{
    Fecha f;

    printf("\n(dd/mm/aaaa): ");
    scanf("%d %d %d", &f.dia, &f.mes, &f.anio);

}

void mostrar_Fecha(Fecha f)
{
    printf("%02d/%02d/%04d\n", f.dia, f.mes, f.anio);
}
