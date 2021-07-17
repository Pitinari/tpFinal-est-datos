#include "tablahash.h"

#include <stdlib.h>
#include <math.h>

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
struct CasillaHash{
  void *dato;
  bool eliminado;
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
  tabla->elems = malloc(sizeof(struct CasillaHash) * capacidad);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->hash = hash;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->elems[idx].dato = NULL;
    tabla->elems[idx].eliminado = false;
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
    }
  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx, cantColisiones = 0;
  idx = tabla->hash(dato,cantColisiones) % tabla->capacidad;

  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return NULL;
  // Retornar el dato de la casilla si hay concidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato) && !(tabla->elems[idx].eliminado))
    return tabla->elems[idx].dato;
  // Retornar NULL en otro caso.
  else{
    while (tabla->elems[idx].dato){
      if (tabla->comp(tabla->elems[idx].dato, dato) && !(tabla->elems[idx].eliminado))
        return tabla->elems[idx].dato;
      idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;
    }
    return NULL;
  }
}

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned cantColisiones = 0, idx;
  idx = tabla->hash(dato,cantColisiones) % tabla->capacidad;
  
  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = dato;
    return;
  }
  // Sobrescribir el dato si el mismo ya se encontraba en la tabla.
  else if (tablahash_buscar (tabla, dato) == NULL){
    while(tabla->elems[idx].dato){
      if(tabla->elems[idx].eliminado){
        tabla->destr(tabla->elems[idx].dato);
        tabla->elems[idx].dato = dato;
        tabla->elems[idx].eliminado = false;
        tabla->numElems++;
        return;
      }
      idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;
    }
    tabla->elems[idx].dato = dato;
    return;
  }
  else{
    while(!tabla->comp(tabla->elems[idx].dato,dato))
      idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;

    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = dato;
    return;
  }

}

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato) {

  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned idx, cantColisiones = 0;
  idx = tabla->hash(dato,cantColisiones) % tabla->capacidad;

  // Retornar NULL si la casilla estaba vacia.
  if (tabla->elems[idx].dato == NULL)
    return;
  // Retornar el dato de la casilla si hay concidencia.
  else if (tabla->comp(tabla->elems[idx].dato, dato)){
    tabla->elems[idx].eliminado = true;
    return;
  }
  // Retornar NULL en otro caso.
  while (tabla->elems[idx].dato){
    if (tabla->comp(tabla->elems[idx].dato, dato)){
      tabla->elems[idx].eliminado = true;
      return;
    }
    idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;
  }
  return;
}

/*
 * Dado un numero entero positivo, busca el numero primo mayor, mas cercano.
 */
unsigned primo_mas_cercano(unsigned n){

unsigned i,j;

  for (i = n; true; i++) {
    if (i % 2 == 0)
      continue;
    for (j = 3; j <= sqrt(i); j += 2) {
      if (i % j == 0)
        break;
    }
    if (j > sqrt(i))
      return i;
  }
}

/*
 * Dado un numero entero positivo, busca el numero primo mayor, mas cercano.
 */
TablaHash tablahash_agrandar (TablaHash tablaVieja){
  TablaHash tablaNueva = tablahash_crear(primo_mas_cercano(tablaVieja->capacidad * 10),
                         tablaVieja->comp, tablaVieja->destr, tablaVieja->hash);

  for (unsigned i = 0; i < tablaVieja->capacidad ; i++){
    if ((tablaVieja->elems[i].dato != NULL) && (tablaVieja->elems[i].eliminado == false)){
      tablahash_insertar(tablaNueva, tablaVieja->elems[i].dato);
    }
  }
  tablahash_destruir(tablaVieja);
  return tablaNueva;
}