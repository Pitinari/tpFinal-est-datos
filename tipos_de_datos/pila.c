#include "pila.h"

#include <stdlib.h>

//pila_crear: void -> Pila
//Devuelve el estado base de pila
Pila pila_crear (){
	return NULL;
}

//pila_agregar: Pila *void -> Pila
//Toma una pila y un dato, pone el dato por encima
//de la pila y devuelve el nodo superior
Pila pila_agregar (Pila pila, void *dato){
	Pila nodo = malloc(sizeof(struct _Pila));
	nodo->dato = dato;
	nodo->prev = pila;
	return nodo;
}

//pila_primero: Pila -> *void
//Devuelve el primer elemento de la pila
void *pila_primero (Pila pila){
	if (pila == NULL)
		return NULL;
	return pila->dato;
}

//pila_borrar_primero: Pila FuncionDestructora -> Pila
// Toma una pila y una funcion destructora, destruye el dato del
// nodo superior, luego el nodo superior y devuelve el siguiente elemento
Pila pila_borrar_primero (Pila pila, FuncionDestructora destr){
	if(pila == NULL)
		return NULL;

	Pila nodo = pila->prev;
	if (destr != NULL)
		destr(pila->dato);
	free(pila);
	return nodo;
}

//pila_destruir: Pila FuncionDestructora -> void
//Toma una pila y libera los datos de cada nodo recursivamente
void pila_destruir (Pila pila, FuncionDestructora destr){
	if (pila != NULL){
		Pila nodo = pila->prev;
		if (destr != NULL)
			destr(pila->dato);
		free(pila);
		pila_destruir(nodo,destr);
	}
}
