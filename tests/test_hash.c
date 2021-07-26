#include "../contacto.h"
#include "../tipos_de_datos/tablahash.h"
#include "../utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 11
/** Capacidad inicial para la tabla hash */

/**
 * Caso de prueba: Tabla hash para contactos
 */
void test_tablaHash() {

  // Iniciar tabla hash
  TablaHash tabla = tablahash_crear(
      CAPACIDAD_INICIAL, (FuncionComparadora)contacto_comparar,
      (FuncionDestructora)contacto_eliminar, (FuncionHash)contacto_hash
      , (FuncionCopiadora)contacto_copiar);

  // Contactos
  Contacto agenda[6];
  agenda[0] = contacto_crear("Pepe", "Argento", 61, "3412695452");
  agenda[1] = contacto_crear("Moni", "Argento", 60, "3412684759");
  agenda[2] = contacto_crear("Coqui", "Argento", 32, "3415694286");
  agenda[3] = contacto_crear("Paola", "Argento", 29, "3416259862");
  agenda[4] = contacto_crear("Maria", "Elena Fuseneco", 59, "3416874594");
  agenda[5] = contacto_crear("Dardo", "Fuseneco", 64, "3416894526");

  // Insertar
  printf("Insercion:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Insertando el contacto: ");
    contacto_mostrar(agenda[i]);
    printf(" en la casilla %d.\n",
           contacto_hash(agenda[i],0) % tablahash_capacidad(tabla));
    tablahash_insertar(tabla, agenda[i]);
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Buscando el contacto: ");
    contacto_mostrar(agenda[i]);
    puts("");
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla.\n");
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Eliminar
  printf("\nEliminacion:\n");
  for (int i = 5; i > 2; --i) {
    printf("Eliminando el contacto: ");
    contacto_mostrar(agenda[i]);
    puts("");
    tablahash_eliminar(tabla, agenda[i]);
  }

  // Buscar
  printf("\nBusqueda:\n");
  for (int i = 0; i < 6; ++i) {
    printf("Buscando el contacto: ");
    contacto_mostrar(agenda[i]);
    puts("");
    Contacto *ret = tablahash_buscar(tabla, agenda[i]);
    if (ret != NULL)
      printf("\tSe encuentra en la tabla.\n");
    else
      printf("\tNo se encuentra en la tabla.\n");
  }

  // Sobrescribir un contacto
  Contacto nuevoContacto = contacto_crear("Pepe", "Argento", 71, "3410000000");
  printf("\nSobrescribiendo el contacto: ");
  contacto_mostrar(agenda[0]);
  printf("\n\tpor: ");
  contacto_mostrar(nuevoContacto);
  puts("");
  tablahash_insertar(tabla, nuevoContacto);
  // Chequeamos que se haya sobrescrito
  Contacto ret = tablahash_buscar(
      tabla, agenda[0]); // Es equivalente a buscar nuevoContacto porque se
                         // compara por nombre
  printf("El nuevo contacto es: ");
  contacto_mostrar(ret);
  puts("");

  // Liberar memoria
  tablahash_destruir(tabla);
  for (int i = 0; i < 6; ++i)
    free(agenda[i]);
  free(nuevoContacto);

  return;
}