#include "listaNelem.h"

#include <stdlib.h>

ListaDoEn listaDoEn_crear (){
    return NULL;
}

ListaDoEn listaDoEn_agregar (ListaDoEn listaDoble, void *dato){
    ListaDoEn nodo = malloc(sizeof(struct _ListaDobleEnlazada));
    nodo->dato = dato;
    nodo->prev = NULL;
    nodo->sig = listaDoble;
    if (listaDoble != NULL)
        listaDoble->prev = nodo;
    return nodo;
}

ListaNelem listaNelem_crear (unsigned capacidad, FuncionDestructora destr){
    ListaNelem lista = malloc(sizeof(struct _ListaNelem));
    lista->actual = listaDoEn_crear ();
    lista->ultimo = listaDoEn_crear ();
    lista->capacidad = capacidad;
    lista->numElems = 0;
    lista->destr = destr;
    return lista;
}

void listaNelem_agregar (ListaNelem lista, void *dato){
    if (lista->capacidad == 0)
        return;
    if (lista->actual == NULL && lista->ultimo == NULL){
        lista->ultimo = listaDoEn_agregar (lista->ultimo, dato);
        lista->actual = lista->ultimo;
        lista->numElems++;
        return;
    }
    if (lista->numElems == lista->capacidad){
        ListaDoEn aux = lista->ultimo;
        lista->ultimo = lista->ultimo->prev;
        lista->destr(aux);
        free(aux);
        if (lista->ultimo != NULL){
            lista->ultimo->sig == NULL;
            lista->actual = listaDoEn_agregar(lista->actual, dato);
        }
        else
            lista->actual = listaDoEn_agregar(lista->ultimo, dato);
        return;
    }
    lista->actual = listaDoEn_agregar(lista->actual, dato);
    lista->numElems++;
}

void listaNelem_destruir (ListaNelem lista){
    if (lista->ultimo == NULL){
        free(lista);
        return;
    }
    ListaDoEn nodo = lista->ultimo->prev;
    if(nodo == NULL){
        lista->destr(lista->ultimo->dato);
        free(lista->ultimo);
        free(lista);
        return;
    }
    while (nodo->prev != NULL){
        nodo = nodo->prev;
        lista->destr(nodo->sig->dato);
        free(nodo->sig);
    }
    lista->destr(nodo->dato);
    free(nodo);
    free(lista);
    return;
}

void *listaNelem_dato_actual (ListaNelem lista){
    if(lista->actual == NULL)
        return NULL;
    return lista->actual->dato;
}

void listaNelem_moverse_siguiente (ListaNelem listaNelem){
    if (listaNelem->actual == NULL){
        return;
    }
    ListaDoEn aux = listaNelem->actual;
    listaNelem->actual = listaNelem->actual->sig;
    listaNelem->numElems--;
    listaNelem->destr(aux->dato);
    free(aux);
    if(listaNelem->actual == NULL && listaNelem->ultimo != NULL)
        listaNelem->ultimo = NULL;
    return;
}