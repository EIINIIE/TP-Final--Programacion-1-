#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

// ------- Estructura Cliente -------
typedef struct
{
    char dni[15]; /// puede tener puntos, guines y ceros iniciales (esto lo agrego para que no alla errores)
    char nombre[50];
    char telefono[20]; /// por lo que se en entero tien limites por eso lo hacemos tipo char tambien porque puede llevar simbolos
    char direccion[30];
    char rol[15];
} Cliente;

// ------- Prototipo -------
Cliente cargar_persona();

#endif // CLIENTE_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
