#ifndef PILA_H
#define PILA_H

#include <stdlib.h>

typedef void (*FuncionDestructora)(void *dato);

struct _Pila {
	void *dato;
    struct _Pila *prev;
};

typedef struct _Pila *Pila;

Pila pila_crear ();

Pila pila_agregar (Pila pila, void *dato);

void *pila_primero (Pila pila);

Pila pila_borrar_primero (Pila pila, FuncionDestructora destr);

void pila_destruir (Pila pila, FuncionDestructora destr);

#endif