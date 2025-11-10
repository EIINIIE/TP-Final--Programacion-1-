#ifndef AUTOS_DISPONIBLES_H_INCLUDED
#define AUTOS_DISPONIBLES_H_INCLUDED

#define MAX_AUTOS 10

typedef struct
{
    int id;
    char marca[30];
    char modelo[30];
    int anio;
    float precio;
} stAuto;

extern stAuto autos[MAX_AUTOS];  /// porque pusieron este tipo de dato??? (extern)
extern int cantidad_autos; /// porque pusieron este tipo de dato??? (extern)

void mostrar_todos_autos_disponibles();

#endif // AUTOS_DISPONIBLES_H_INCLUDED
