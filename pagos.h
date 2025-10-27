#ifndef PAGOS_H_INCLUDED
#define PAGOS_H_INCLUDED

#include "fecha.h"

// ------- Estructura Empleado -------
typedef struct stPago
{
    int idPago;                // ID único del pago
    char dniCliente[15];       // Cliente que realiza el pago
    float monto;
    Fecha fechaPago;
    char medioPago[20];        // Efectivo, tarjeta, transferencia, etc.
} Pago;

// ------- Prototipo -------
float medioDPago(float precioBase);

#endif // PAGOS_H_INCLUDED
