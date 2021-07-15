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
Contacto contacto_crear (char *nombre, char *apellido, int edad, char *telefono);

//elimina un contacto
void contacto_eliminar (Contacto cont);

//compara un contacto, con un nombre y un apellido, devuelve true si son los mismos y false en caso contrario
bool contacto_comparar (Contacto cont1, Contacto cont2);

//reemplaza la edad y el telefono de un contacto
void contacto_reemplazar_datos (Contacto cont, int edadNueva, char *telefonoNuevo);

//Muestra en pantalla el contacto
void contacto_mostrar (Contacto cont);

//Utilizada para obtener la posicion en la tabla hash
unsigned contacto_hash (Contacto cont, unsigned cantidadColisiones)

#endif