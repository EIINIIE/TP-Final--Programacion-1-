#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

// ------- Definici�n de Archivo Centralizada -------
#define ARCHIVO_EMPLEADOS "empleados.bin" // <--- A�ADIDO (y unificado)

// ------- Estructura Empleado -------

typedef struct
{
    char correo[50];
    char contrasena[50];
    int dni;
    int dia;
    int mes;
    int anios;
    char rol[30];
} stEmpleado;

// ------- Prototipo -------
int iniciarSesion_empleado();
void menu_empleado_directo();





#endif // EMPLEADO_H_INCLUDED
///Esto va al final porque #endif es el cierre de una condici�n
