#ifndef CONTACTO_H
#define CONTACTO_H

#include <stdbool.h>

struct _Contacto {
    char *nombre;
    char *apellido;
    unsigned edad;
    char *telefono;
};

typedef struct _Contacto *Contacto;

//crea un contacto con los datos otorgados
Contacto contacto_crear (char *nombre, char *apellido, unsigned edad, char *telefono);

//elimina un contacto
void contacto_eliminar (void *cont);

//compara un contacto, con un nombre y un apellido, devuelve true si son los mismos y false en caso contrario
bool contacto_comparar (void *cont1, void *cont2);

//reemplaza la edad y el telefono de un contacto
void contacto_reemplazar_datos (Contacto cont, unsigned edadNueva, char *telefonoNuevo);

//Muestra en pantalla el contacto
void contacto_mostrar (Contacto cont);

//Utilizada para obtener la posicion en la tabla hash
unsigned contacto_hash (void *cont, unsigned cantidadColisiones);

//Retorna true si el nombre es valido y false en caso contrario
bool contacto_validar_nombre (char *nombre);

//Retorna true si el telefono es valido y false en caso contrario
bool contacto_validar_telefono (char *telefono);

void *contacto_copiar (void *cont);

typedef enum {Agregar,Eliminar,Editar} Accion;
// Se define este dato para las acciones de deshacer y rehacer
struct _Contacto_Accion{
    Contacto cont;
    Accion acc;
};

typedef struct _Contacto_Accion *ContactoAcc;

ContactoAcc contactoAcc_crear (Contacto cont, Accion acc);

void contactoAcc_destruir (void *contAcc);

int contacto_comparar_nombre(void *dato1, void* dato2);

int contacto_comparar_apellido(void *dato1, void* dato2);

int contacto_comparar_telefono(void *dato1, void* dato2);

int contacto_comparar_edad(void *dato1, void* dato2);

#endif