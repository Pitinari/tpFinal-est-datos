#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stdbool.h>

typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef bool (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un booleano que es true si los datos son iguales y false en caso
contrario */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato, unsigned cantColisiones);
/** Retorna un entero sin signo para el dato */

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
  FuncionCopiadora copia;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionHash hash;
};

typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionComparadora comp,
                         FuncionDestructora destr, FuncionHash hash,
                         FuncionCopiadora copia);

/**
 * Retorna el numero de elementos de la tabla.
 */
unsigned tablahash_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
unsigned tablahash_capacidad(TablaHash tabla);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla);

/**
 * Inserta un dato en la tabla, o lo reemplaza si ya se encontraba.
 */
void tablahash_insertar(TablaHash tabla, void *dato);

/**
 * Retorna el dato de la tabla que coincida con el dato dado, o NULL si el dato
 * buscado no se encuentra en la tabla.
 */
void *tablahash_buscar(TablaHash tabla, void *dato);

/**
 * Elimina el dato de la tabla que coincida con el dato dado.
 */
void tablahash_eliminar(TablaHash tabla, void *dato);

void *tablahash_a_lista (TablaHash tabla);

#endif /* __TABLAHASH_H__ */