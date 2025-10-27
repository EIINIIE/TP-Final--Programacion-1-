#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include "fecha.h"

/// faltaria implementarlo

#define ARCHIVO_AUTOS "autos.dat"
#define ARCHIVO_CLIENTES "clientes.dat"
#define ARCHIVO_VENTAS "ventas.dat"

// ------- Estructura Venta -------
typedef struct stVenta
{
    Fecha fecha;
    char patenteAutoVendido[11];
    float precioVenta;
    float ganancia;
    char dniComprador[15]; // Usar char para mantener coherencia con las estructuras
    char dniVendedor[15];  // Usar char para mantener coherencia con las estructuras
} Venta;

// ------- Prototipo -------
Venta cargarVenta();
void registrarVenta();
void mostrarVenta(Venta ventas);
void mostrarVentas();

#endif // VENTA_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
