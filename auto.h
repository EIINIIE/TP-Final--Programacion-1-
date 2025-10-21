#ifndef AUTO_H_INCLUDED
#define AUTO_H_INCLUDED


#include "persona.h"  // Incluye Persona porque Auto tiene un titular

#define ARCHIVO_AUTOS "autos.bin"

// ------- Estructura Auto -------
typedef struct
{
    char patente[11]; // AB-1234-CD o ABC-123
    char marca[20];
    char modelo[20];
    int anio;
    int kms;
    Persona titular; // Titular del auto
    float precioDeAdquisicion;
    float precioFinal;
} Auto;


// ------- Prototipos -------
Auto cargar_auto();
void agregar_autos();
void mostrar_auto(Auto autos);
void mostrar_autos(char archivo[]);
float medioDPago(float precioDeAdquisicion);
Auto modificar_auto();

#endif // AUTO_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
