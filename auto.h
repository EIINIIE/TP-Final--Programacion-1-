#ifndef AUTO_H_INCLUDED
#define AUTO_H_INCLUDED

#include "cliente.h"

#define ARCHIVO_AUTOS "autos.bin"

// ------- Estructura Auto (Stock de la Empresa) -------
typedef struct
{
    char patente[11];
    char marca[20];
    char modelo[20];
    int anio;
    int kms;
    Cliente titular;
    float precioDeAdquisicion;
    float precioFinal;
} Auto;

// ------- Prototipos -------
Auto cargar_auto();
void agregar_autos(); // Esta es para clientes que traen su auto
void mostrar_auto(Auto autos);
void mostrar_todos_autos(char archivo[]);
float medioDPago(float precioDeAdquisicion);

// --- NUEVA FUNCION PARA EL GERENTE ---
void agregar_auto_stock();

#endif // AUTO_H_INCLUDED
