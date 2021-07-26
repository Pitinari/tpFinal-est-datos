#include "test_pila.h"
#include "../tipos_de_datos/pila.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_pila(){
    Pila pila = pila_crear();
    pila = pila_agregar (pila, "hola");
    assert(pila);
    pila = pila_agregar (pila, "mundo");
    assert(!strcmp(pila_primero(pila),"mundo"));
    pila_destruir(pila,NULL);

    pila = pila_crear();
    char *texto1, *texto2;
    texto1 = malloc(sizeof(char)*10);
    texto2 = malloc(sizeof(char)*10);
    strcpy(texto1,"hola");
    strcpy(texto2,"mundo");
    pila = pila_agregar (pila, texto1);
    pila = pila_agregar (pila, texto2);
    pila = pila_borrar_primero(pila,free);
    assert(!strcmp(pila_primero(pila),"hola"));
    pila_destruir(pila,free);
}