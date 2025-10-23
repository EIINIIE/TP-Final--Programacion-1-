#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

typedef struct stFecha {
    int dia;
    int mes;
    int anio;
} Fecha;

void cargar_Fecha();

#endif // FECHA_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
