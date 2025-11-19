#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct
{
    char dni[30];
    char nombre[50];
    char telefono[20];
    char direccion[30];
    char rol[15];
} Cliente;

// ------- Prototipos -------
Cliente cargar_persona();
void guardar_cliente_en_archivo(Cliente c);
void modificar_cliente();  // <-- prototipo

#endif // CLIENTE_H_INCLUDED
