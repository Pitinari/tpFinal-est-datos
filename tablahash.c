#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
struct CasillaHash{
  void *dato;
  struct CasillaHash *sig;
};

/**
 * Estructura principal que representa la tabla hash.
 */
struct _TablaHash {
  struct CasillaHash *elems;
  unsigned numElems;
  unsigned capacidad;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionComparadora comp,
                         FuncionDestructora destr, FuncionHash hash) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  assert(tabla != NULL);
  tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
  assert(tabla->elems != NULL);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].sig = NULL;
  }

  return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL){
      tabla->destr(tabla->elems[idx].dato);
      if (tabla->elems[idx].sig != NULL){
        struct CasillaHash *nodo = tabla->elems[idx].sig;
        while (nodo){
          tabla->destr(nodo->dato);
          nodo = nodo->sig;
        }
      }
    }
  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 * IMPORTANTE: La implementacion no maneja colisiones.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = dato;
    return;
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else if (tabla->comp(tabla->elems[idx].dato, dato)) {
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = dato;
    return;
  }
  // Si hay colision de datos, crea una linked list en la casilla
  else {
    struct CasillaHash *nodo = tabla->elems[idx].sig;
    while (!nodo){
      if (tabla->comp(nodo->dato, dato)){
        tabla->destr(nodo->dato);
        nodo->dato = dato;
      }
      nodo = nodo->sig;
    }
    nodo = malloc(sizeof(struct CasillaHash));
    nodo->dato = dato;
    nodo->sig = NULL;
  }
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return NULL;
  // Retornar el dato de la casilla si hay concidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato))
    return tabla->elems[idx].dato;
  // Retornar NULL en otro caso.
  else{
    struct CasillaHash *nodo = tabla->elems[idx].sig;
    while (!nodo){
      if (tabla->comp(nodo->dato, dato)){
        return nodo->dato;
      }
      nodo = nodo->sig;
    }
    return nodo;
  }
    
}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx = tabla->hash(dato) % tabla->capacidad;

  // Retornar si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;
  // Vaciar la casilla si hay coincidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato)) {
    tabla->numElems--;
    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = NULL;
    return;
  }
}
