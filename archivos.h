#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "tipos_de_datos/tablahash.h"
#include "contacto.h"

#include <stdlib.h>

unsigned int string_a_unsigned(char *st);

void cargar(TablaHash tabla, char *buffer);

void guardar(TablaHash tabla, char *buffer);

void guardar_ordenado (TablaHash tabla, char *nombreArchivo, char *argumento);

#endif