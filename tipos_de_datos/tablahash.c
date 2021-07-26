#include "tablahash.h"

#include <stdlib.h>
#include <math.h>

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionComparadora comp,
                         FuncionDestructora destr, FuncionHash hash,
                         FuncionCopiadora copia) {

  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash tabla = malloc(sizeof(struct _TablaHash));
  tabla->elems = malloc(sizeof(struct CasillaHash) * capacidad);
  tabla->numElems = 0;
  tabla->capacidad = capacidad;
  tabla->copia = copia;
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
unsigned tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
unsigned tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

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
  // Retornar el dato de la casilla si hay concidencia y no esta anteriormente eliminado.
  else if (tabla->comp(tabla->elems[idx].dato, dato) && !(tabla->elems[idx].eliminado))
    return tabla->elems[idx].dato;
  // En otro caso hay una colision
  else{
    //comenzamos a buscar nuevos hash para el dato, hasta que 
    //haya coincidencia
    while (tabla->elems[idx].dato != NULL){
      if (tabla->comp(tabla->elems[idx].dato, dato)){
        if (!(tabla->elems[idx].eliminado))
          //coincidencia y no eliminado
          return tabla->elems[idx].dato;
        else
          //coincidencia pero eliminado
          return NULL;
      }
      idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;
    }
    // si sale del while por una casilla nula, entonces no esta en la tabla
    return NULL;
  }
}

/*
 * primo_mas_cercano: unsigned -> unsigned
 * Dado un numero entero positivo, busca el numero primo mayor, mas cercano.
 */
unsigned primo_mas_cercano(unsigned n){

unsigned i,j;

  for (i = n; true; i++) {
    if (i % 2 == 0) //si es par no hace nada
      continue;
    for (j = 3; j <= sqrt(i); j += 2) {
      if (i % j == 0) //si es impar pregunta si es multiplo de alguno de los
        break;      //impares (menos el 1) hasta su raiz cuadrada
    }
    if (j > sqrt(i))
      return i;
  }
}

/*
 * tablahash_agrandar: TablaHash -> void
 * Dado un numero entero positivo, busca el numero primo mayor, mas cercano.
 */
void tablahash_agrandar (TablaHash tablaVieja){
  //busca un primo aproximadamente 10 veces mas grande, crea un array de casillas de ese tamano y guarda el array viejo
  unsigned capacidadVieja = tablahash_capacidad(tablaVieja),capacidadNueva = primo_mas_cercano(tablahash_capacidad(tablaVieja) * 5);
  struct CasillaHash *antigua = tablaVieja->elems;
  tablaVieja->elems = malloc(sizeof(struct CasillaHash) * capacidadNueva);
  tablaVieja->numElems = 0;
  tablaVieja->capacidad = capacidadNueva;

  //inicializa el array nuevo
  for (unsigned idx = 0; idx < capacidadNueva; ++idx) {
    tablaVieja->elems[idx].dato = NULL;
    tablaVieja->elems[idx].eliminado = false;
  }

  //ingresa todos los elementos del array viejo en el nuevo
  for (unsigned i = 0; i < capacidadVieja ; i++){
    if ((antigua[i].dato != NULL) && (antigua[i].eliminado == false)){
      tablahash_insertar(tablaVieja, antigua[i].dato);
      tablaVieja->destr(antigua[i].dato); //libera el dato del array viejo
    }
  }
  free(antigua); //libera el array viejo
  return;
}

/**
 * tablahash_insertar: TablaHash *void -> void
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato) {

  //agranda la tabla si tiene un 70% ocupado
  if (((float)tablahash_nelems(tabla) / (float)tablahash_capacidad(tabla)) > 0.7)
    tablahash_agrandar(tabla);
  
  // Calculamos la posicion del dato dado, de acuerdo a la funcion hash.
  unsigned cantColisiones = 0, idx;
  idx = tabla->hash(dato,cantColisiones) % tabla->capacidad;
  
  // Insertar el dato si la casilla estaba libre.
  if (tabla->elems[idx].dato == NULL) {
    tabla->numElems++;
    tabla->elems[idx].dato = tabla->copia(dato);
    return;
  }
  // busca si el dato ya esta en la tabla
  else if (tablahash_buscar (tabla, dato) == NULL){
    // en caso de no estarlo, itera hasta encontrar una casilla
    // libre o eliminada
    while(tabla->elems[idx].dato){
      if(tabla->elems[idx].eliminado){
        tabla->destr(tabla->elems[idx].dato);
        tabla->elems[idx].dato = tabla->copia(dato);
        tabla->elems[idx].eliminado = false;
        tabla->numElems++;
        return;
      }
      idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;
    }
    tabla->elems[idx].dato = tabla->copia(dato);
    tabla->numElems++;
    return;
  }
  else{ //sino itera hasta encontrar al contacto
    while(!tabla->comp(tabla->elems[idx].dato,dato))
      idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;

    tabla->destr(tabla->elems[idx].dato);
    tabla->elems[idx].dato = tabla->copia(dato);
    return;
  }

}

/**
 * tablahash_eliminar: TablaHash *void -> void
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
    tabla->numElems--;
    return;
  }
  // iterar mientras las casillas sean ocupadas
  while (tabla->elems[idx].dato){
    if (tabla->comp(tabla->elems[idx].dato, dato)){
      //si hay coincidencia y no esta eliminado
      if (tabla->elems[idx].eliminado == false){
        tabla->elems[idx].eliminado = true;
        tabla->numElems--;
        //lo elimina y resta del numero de elementos
      }
      return;
    }
    idx = tabla->hash(dato,++cantColisiones) % tabla->capacidad;
  }
  return; //llego a una casilla NULL
}

// tablahash_a_lista: TablaHash -> *void
// Dada una tabla hash y una lista de contactos del tamano de la cantidad
// de posiciones ocupadas en la tabla hash, hace que todos los punteros de 
// la lista apunten a los elementos de la tabla
void *tablahash_a_lista (TablaHash tabla){
  unsigned j = 0;
  void **lista = malloc(sizeof(void*)*tabla->numElems);
  for (unsigned i = 0; i < tabla->capacidad ; i++){
    if(tabla->elems[i].dato == NULL || tabla->elems[i].eliminado == true)
      continue;
    lista[j++] = tabla->elems[i].dato;
  }
  return lista;
}