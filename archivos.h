#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "tipos_de_datos/tablahash.h"

#include <stdlib.h>

unsigned int string_a_unsigned(char *st);

void cargar(TablaHash *tabla);

void guardar(TablaHash *tabla);

#endif