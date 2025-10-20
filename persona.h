#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED


// ------- Estructura Persona -------
typedef struct
{
    char dni[15];
    char nombre[50];
    char telefono[20];
    char direccion[30];
    char rol[15];
} Persona;

// ------- Prototipo -------
Persona cargar_persona();

#endif // PERSONA_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
