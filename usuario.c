#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"
#include "auto_cliente.h" // Asegúrate de tener este include para agregar_autos
#include "autos_disponibles.h" // Para mostrar_todos_autos_disponibles
#include "cliente.h" // Para cargar_persona
#include "pagos.h"

#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_AUTOS "autos.bin"

// FUNCION 1: Verifica si un usuario ya existe por correo
int usuario_existente(char correo[])
{
    FILE* file = fopen(ARCHIVO_CLIENTES, "rb");
    if(file == NULL) return 0;

    stUsuario usuario;
    while(fread(&usuario, sizeof(stUsuario), 1, file) == 1)
    {
        if(strcmp(usuario.correo, correo) == 0)
        {
            fclose(file);
            return 1; // Existe
        }
    }
    fclose(file);
    return 0; // No existe
}

// FUNCION 2: Registrar un nuevo usuario
stUsuario registro_Usuario()
{
    stUsuario nuevo;

    printf("\n--- REGISTRO DE USUARIO ---\n");
    printf("Ingrese su correo: ");
    scanf("%49s", nuevo.correo);

    if(usuario_existente(nuevo.correo))
    {
        printf("Este usuario ya esta registrado\n");
        nuevo.dni = -1; // Señal de error
        return nuevo;
    }

    printf("Ingrese su contrasenia: ");
    scanf("%49s", nuevo.contrasena);

    printf("Ingrese su DNI: ");
    scanf("%d", &nuevo.dni);

    printf("Fecha de nacimiento (dd mm aaaa): ");
    scanf("%d %d %d", &nuevo.dia, &nuevo.mes, &nuevo.anios);

    printf("\nUsuario registrado con exito\n");
    return nuevo;
}

// FUNCION 3: Guardar usuario en archivo
void guardar_Usuario(stUsuario usuario)
{
    FILE *file = fopen(ARCHIVO_CLIENTES, "ab");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(&usuario, sizeof(stUsuario), 1, file);
    fclose(file);
}

// FUNCION 4: Verificar si correo y contraseña coinciden
int verificar_Usuario(char correo[], char contrasena[])
{
    FILE *file = fopen(ARCHIVO_CLIENTES, "rb");
    if(file == NULL) return 0;

    stUsuario usuario;
    int encontrado = 0;

    while(fread(&usuario, sizeof(stUsuario), 1, file) == 1)
    {
        if(strcmp(usuario.correo, correo) == 0 && strcmp(usuario.contrasena, contrasena) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    fclose(file);
    return encontrado;
}

// FUNCION 5: Iniciar sesión e ingresar al menú del cliente
void iniciarSesion()
{
    char correo[50], contrasena[50];
    printf("\n------ INICIAR SESION ------\n");
    printf("Correo: ");
    scanf("%49s", correo);
    printf("Contrasena: ");
    scanf("%49s", contrasena);
    system("cls");

    if(verificar_Usuario(correo, contrasena))
    {
        printf("\nSesion iniciada correctamente\n\n");

        int opcion_sesion;
        do
        {
            printf("-------------------------------------\n");
            printf("1. Datos del cliente\n");
            printf("2. Dato del auto del cliente\n");
            printf("3. Autos disponibles\n");
            printf("4. Pagos\n");
            printf("5. Volver al inicio\n");
            printf("0. Salir\n");
            printf("-------------------------------------\n");
            printf("\nElija una opcion: ");
            scanf("%d", &opcion_sesion);
            system("cls");

            switch(opcion_sesion)
            {
            case 0:
                printf("Saliendo...\n");
                return;

            case 1:
                // Necesitas implementar mostrar datos del cliente logueado
                // Por ahora llamamos a cargar para probar
                cargar_persona();
                break;

            case 2:
                agregar_autos_cliente();
                break;

            case 3:
                mostrar_todos_autos_disponibles();
                break;

            case 4:
                // Antes decia: printf("Funcion de pagos aqui\n");
                // Ahora llamamos a la funcion real:
                gestionDePagos();
                break;

            case 5:
                printf("Volviendo al inicio...\n");
                opcion_sesion = 0;
                break;

            default:
                printf("Opcion no valida\n");
                break;
            }
            system("pause");
            system("cls");
        }
        while(opcion_sesion != 0);
    }
    else
    {
        printf("\nCorreo o contrasenia incorrectos\n");
    }
}

/// Nuevo Recursivo

void mostrarTodosLosUsuarios()
{
    stUsuario usuarios[100];
    int cantidad = cargarUsuariosEnArreglo(usuarios, 50); /// la cantidad seria los datos cargados de los usuarios

    if(cantidad == 0)
    {
        printf("No hay usuarios registrados.\n");
        return;
    }

    printf("\n--- LISTA DE USUARIOS (Recursivo) ---\n");
    mostrarUsuariosRecursivo(usuarios, 0, cantidad);
}


int cargarUsuariosEnArreglo(stUsuario arr[], int tope) /// el int tope le doy un valor de 50
{
    FILE* file = fopen(ARCHIVO_CLIENTES, "rb");
    if(file == NULL)
    {
        return 0;
    }

    int i = 0;
    while(i < tope && fread(&arr[i], sizeof(stUsuario), 1, file) == 1)
    {
        i++;
    }
    fclose(file);
    return i;
}

void mostrarUsuariosRecursivo(stUsuario arr[], int pos, int total) /// el pos es la posicion estas posicionado en 0 /// total es la cantidad de usuarios cargados
{
    if(pos == total)
    {
        return;
}
    // Mostrar usuario
    printf("Correo: %s\n", arr[pos].correo);
    printf("DNI: %d\n", arr[pos].dni);
    printf("Nacimiento: %d/%d/%d\n", arr[pos].dia, arr[pos].mes, arr[pos].anios);
    printf("-------------------------------------\n");

    mostrarUsuariosRecursivo(arr, pos + 1, total);
}

