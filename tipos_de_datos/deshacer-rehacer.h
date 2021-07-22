#ifndef DESHACERREHACER_H
#define DESHACERREHACER_H

#include <stdlib.h>

struct _ListaDobleEnlazada{
	void *dato;
	struct _ListaDobleEnlazada *prev;
	struct _ListaDobleEnlazada *sig;
};

typedef struct _ListaDobleEnlazada *ListaDoEn;

struct _ListaNelem{
	ListaDoEn actual;
	ListaDoEn ultimo;
	unsigned capacidad;
	unsigned numElems;
};

typedef struct _ListaNelem *ListaNelem;

ListaNelem listaNelem_crear (unsigned capacidad);

void listaNelem_agregar (ListaNelem lista, void *dato);

void listaNelem_destruir (ListaNelem lista);

ListaNelem

#endif