#include "pila.h"

#include <stdlib.h>

Pila pila_crear (){
	return NULL;
}

Pila pila_agregar (Pila pila, void *dato){
	Pila nodo = malloc(sizeof(struct _Pila));
	nodo->dato = dato;
	nodo->prev = pila;
	return nodo;
}

void *pila_primero (Pila pila){
	return pila->dato;
}

Pila pila_borrar_primero (Pila pila, FuncionDestructora destr){
	if(pila == NULL)
		return NULL;

	Pila nodo = pila->prev;
	destr(pila->dato);
	free(pila);
	return nodo;
}

void pila_destruir (Pila pila, FuncionDestructora destr){
	if (pila != NULL){
		Pila nodo = pila->prev;
		destr(pila->dato);
		free(pila);
		pila_destruir(nodo,destr);
	}
}