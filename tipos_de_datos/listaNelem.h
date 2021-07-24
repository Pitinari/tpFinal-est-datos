#ifndef LISTANELEM_H
#define LISTANELEM_H

#include <stdlib.h>

struct _ListaDobleEnlazada{
	void *dato;
	struct _ListaDobleEnlazada *prev;
	struct _ListaDobleEnlazada *sig;
};

typedef struct _ListaDobleEnlazada *ListaDoEn;

typedef void (*FuncionDestructora)(void *dato);

struct _ListaNelem{
	ListaDoEn actual;
	ListaDoEn ultimo;
	unsigned capacidad;
	unsigned numElems;
	FuncionDestructora destr;
};

typedef struct _ListaNelem *ListaNelem;


ListaNelem listaNelem_crear (unsigned capacidad, FuncionDestructora destr);

void listaNelem_agregar (ListaNelem lista, void *dato);

void listaNelem_eliminar_prev (ListaNelem lista);

void listaNelem_destruir (ListaNelem lista);

void *listaNelem_dato_actual (ListaNelem lista);

void listaNelem_moverse_siguiente (ListaNelem listaNelem);

#endif