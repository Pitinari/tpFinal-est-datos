#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stdbool.h>

typedef bool (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un booleano que es true si los datos son iguales y false en caso
contrario */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato, unsigned cantColisiones);
/** Retorna un entero sin signo para el dato */

typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionComparadora comp,
                         FuncionDestructora destr, FuncionHash hash);

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla);

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla);

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

/*
 * Dado un numero entero positivo, busca el numero primo mayor, mas cercano.
 */
unsigned primo_mas_cercano(unsigned n);

/*
 * Dado un numero entero positivo, busca el numero primo mayor, mas cercano.
 */
TablaHash tablahash_agrandar (TablaHash tablaVieja);

#endif /* __TABLAHASH_H__ */