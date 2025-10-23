#ifndef GERENTE_H_INCLUDED
#define GERENTE_H_INCLUDED

// ------- Estructura Gerente -------
typedef struct
{
    char correo[50];
    char contrasena[50];
    int dni;
    int dia;
    int mes;
    int anios;
} stGerente;

// ------- Prototipo -------
int iniciarSesionGerente();



#endif // GERENTE_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
