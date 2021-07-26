#include "listaNelem.h"

#include <stdlib.h>

//listaDoEn_crear: void -> ListaDoEn
ListaDoEn listaDoEn_crear (){
    return NULL;
}

//listaDoEn_agregar: ListaDoEn *void -> ListaDoEn
// Recibe una lista doblemente enlazada y un dato, crea un nodo nuevo
// y lo agrega al principio de la lista
ListaDoEn listaDoEn_agregar (ListaDoEn listaDoble, void *dato){
    ListaDoEn nodo = malloc(sizeof(struct _ListaDobleEnlazada));
    nodo->dato = dato;
    nodo->prev = NULL;
    nodo->sig = listaDoble;
    if (listaDoble != NULL)
        listaDoble->prev = nodo;
    return nodo;
}

//listaNelem_crear: unsigned FuncionDestructora -> ListaNelem
//Dada una capacidad y una funcion para destruir los datos que se agreguen
// inicializa una ListaNelem
ListaNelem listaNelem_crear (unsigned capacidad, FuncionDestructora destr){
    ListaNelem lista = malloc(sizeof(struct _ListaNelem));
    lista->actual = listaDoEn_crear ();
    lista->ultimo = listaDoEn_crear ();
    lista->capacidad = capacidad;
    lista->numElems = 0;
    lista->destr = destr;
    return lista;
}

//listaNelem_agregar: ListaNelem *void -> void
//Toma un elemento y lo agrega a la lista en la posicion actual
void listaNelem_agregar (ListaNelem lista, void *dato){
    if (lista->capacidad == 0)
        return;// si el tamano es 0, no se hace nada
    if (lista->actual == NULL && lista->ultimo == NULL){
        //si la lista esta vacia se crea un nodo para que el ultimo y
        // el actual apunten a el 
        lista->ultimo = listaDoEn_agregar (lista->ultimo, dato);
        lista->actual = lista->ultimo;
        lista->numElems++;
        return;
    }
    //Si se alcanzo el tamano maximo de la lista, libera un nodo de la ultima
    //posicion y agrega el nuevo en la posicion actual
    if (lista->numElems == lista->capacidad){
        ListaDoEn aux = lista->ultimo;
        lista->ultimo = lista->ultimo->prev;
        if (lista->destr != NULL)
            lista->destr(aux->dato);
        free(aux);
        if (lista->ultimo != NULL){
            lista->ultimo->sig = NULL;
            lista->actual = listaDoEn_agregar(lista->actual, dato);
        }
        else
            lista->actual = listaDoEn_agregar(lista->ultimo, dato);
        return;
    }
    lista->actual = listaDoEn_agregar(lista->actual, dato);
    lista->numElems++;
}

//listaNelem_destruir: ListaNelem -> void
//libera la lista, nodo a nodo
void listaNelem_destruir (ListaNelem lista){
    if (lista->ultimo == NULL){
        free(lista);
        return;
    }
    while (lista->ultimo != NULL){
        listaNelem_moverse_siguiente(lista);
    }
    free(lista);
    return;
}

//listaNelem_dato_actual: ListaNelem -> *void
//devuelve el dato actual
void *listaNelem_dato_actual (ListaNelem lista){
    if(lista->actual == NULL)
        return NULL;
    return lista->actual->dato;
}

//listaNelem_moverse_siguiente: ListaNelem -> void
//Libera el nodo de actual y lo mueve una posicion "abajo"
void listaNelem_moverse_siguiente (ListaNelem listaNelem){
    if (listaNelem->actual == NULL){
        return;
    }
    ListaDoEn aux = listaNelem->actual;
    listaNelem->actual = listaNelem->actual->sig;
    listaNelem->numElems--;
    if (listaNelem->destr != NULL)
        listaNelem->destr(aux->dato);
    free(aux);
    if(listaNelem->actual == NULL && listaNelem->ultimo != NULL)
        listaNelem->ultimo = NULL;
    return;
}