#ifndef SEMAEDADES_H
#define SEMAEDADES_H

#include "contacto.h"
#include "tipos_de_datos/pila.h"

#include <stdlib.h>
#include <stdbool.h>

bool **generar_tabla_sumaEdades (Contacto *contactos, unsigned cantContactos, unsigned suma);

void destruir_tabla_sumaEdades (bool **tabla, unsigned cantContactos);

Pila subconjunto_contactos_suma(bool **tabla, Contacto *contactos, unsigned cantContactos, unsigned suma);

#endif