#ifndef AUTO_CLIENTE_H_INCLUDED
#define AUTO_CLIENTE_H_INCLUDED

#include "cliente.h"

#define ARCHIVO_AUTOS_CLIENTE "autos_cliente.bin" // Cambiamos el define para no chocar

// ------- Estructura AutoCliente (Renombrada) -------
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
} AutoCliente; // <--- AQUI ESTA EL CAMBIO CLAVE

// ------- Prototipos -------
AutoCliente cargar_auto_cliente(); // Renombramos funcion
void agregar_autos_cliente();      // Renombramos funcion
void mostrar_auto_cliente(AutoCliente autos); // Renombramos funcion
void mostrar_todos_autos_cliente();
int cargar_autos_cliente_din(AutoCliente **listaAutos);

#endif // AUTO_CLIENTE_H_INCLUDED
