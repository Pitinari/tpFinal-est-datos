#include "../contacto.h"
#include "../tipos_de_datos/tablahash.h"
#include "../utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 5
/** Capacidad inicial para la tabla hash
 *  Es bastante chica para que testee casos en colisiones
 *  y que se agranda
 */

/**
 * Caso de prueba: Tabla hash para contactos
 */
void test_tablaHash() {

  // Iniciar tabla hash
  TablaHash tabla = tablahash_crear(
      CAPACIDAD_INICIAL, (FuncionComparadora)contacto_comparar,
      (FuncionDestructora)contacto_eliminar, (FuncionHash)contacto_hash
      , (FuncionCopiadora)contacto_copiar);
  assert(tabla);

  // Contactos
  Contacto agenda[6];
  agenda[0] = contacto_crear("Pepe", "Argento", 61, "3412695452");
  agenda[1] = contacto_crear("Moni", "Argento", 60, "3412684759");
  agenda[2] = contacto_crear("Coqui", "Argento", 32, "3415694286");
  agenda[3] = contacto_crear("Paola", "Argento", 29, "3416259862");
  agenda[4] = contacto_crear("Maria", "Elena Fuseneco", 59, "3416874594");
  agenda[5] = contacto_crear("Dardo", "Fuseneco", 64, "3416894526");

  // Insertar
  for (int i = 0; i < 6; ++i) {
    assert(agenda[i]);
    tablahash_insertar(tabla, agenda[i]);
  }

  // Agrandar
  assert(tablahash_capacidad(tabla) != CAPACIDAD_INICIAL);

  // Buscar
  for (int i = 0; i < 6; ++i) {
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    assert(ret);
  }

  // Eliminar
  for (int i = 5; i > 2; --i) {
    unsigned numElemsAnt = tablahash_nelems(tabla);
    tablahash_eliminar(tabla, agenda[i]);
    assert(numElemsAnt-1 == tablahash_nelems(tabla));
  }
  

  // Buscar
  for (int i = 0; i < 3; ++i) {
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    assert(ret);
  }
  for (int i = 3; i < 6; ++i) {
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    assert(!ret);
  }

  // Sobrescribir un contacto
  Contacto nuevoContacto = contacto_crear("Pepe", "Argento", 71, "3410000000");
  assert(nuevoContacto);
  tablahash_insertar(tabla, nuevoContacto);
  // Chequeamos que se haya sobrescrito
  Contacto ret = tablahash_buscar(
      tabla, agenda[0]); // Es equivalente a buscar nuevoContacto porque se
                         // compara por nombre
  assert(tabla->comp(ret,nuevoContacto));

  // Liberar memoria
  tablahash_destruir(tabla);
  for (int i = 0; i < 6; ++i)
    free(agenda[i]);
  free(nuevoContacto);

  return;
}