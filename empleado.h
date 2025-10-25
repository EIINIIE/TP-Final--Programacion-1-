#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

// ------- Estructura Empleado -------

typedef struct
{
    char correo[50];
    char contrasena[50];
    int dni;
    int dia;
    int mes;
    int anios;
} stEmpleado;

// ------- Prototipo -------
int iniciarSesion_empleado();
void funcion_iniciarSesion_empleado();



#endif // EMPLEADO_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condición
