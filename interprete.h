#ifndef INTERPRETE_H
#define INTERPRETE_H

#include "tipos_de_datos/tablahash.h"
#include "tipos_de_datos/listaNelem.h"
#include "tipos_de_datos/pila.h"

#include <stdbool.h>

// guarda en memoria un string de largo dinamico, almacenando de a 10
// para que no se utilice realloc en cada caracter
char *ingresar_buffer();

// Recibira un buffer de entrada y decidira que accion tomar y retornara
// un entero dependiendo de si seguir pidiendo entrada
bool interpretar(char *buffer, TablaHash tabla, ListaNelem deshacer, Pila *rehacer);

#endif