#ifndef CONTACTO_H
#define CONTACTO_H

#include <stdbool.h>

struct _Contacto {
    char *nombre;
    char *apellido;
    int edad;
    char *telefono;
};

typedef struct _Contacto *Contacto;

//crea un contacto con los datos otorgados
Contacto crear_contacto (char *nombre, char *apellido, int edad, char *telefono);

//elimina un contacto
void eliminar_contacto (Contacto cont);

//compara dos contactos y retorna true si son iguales, false en caso contrario
bool comparar_contactos (Contacto cont1, Contacto cont2);

//reemplaza la edad y el telefono de un contacto
void reemplazar_datos (Contacto cont, int edad_Nueva, char *telefono_Nuevo);

#endif