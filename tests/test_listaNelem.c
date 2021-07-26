#include "../tipos_de_datos/listaNelem.h"
#include "test_listaNelem.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_listaNelem (){
    ListaNelem lista = listaNelem_crear(2,NULL);
    assert(lista);
    listaNelem_agregar(lista,"Hola");
    listaNelem_agregar(lista,"como");
    listaNelem_agregar(lista,"va");

    assert(!strcmp(listaNelem_dato_actual(lista), "va"));
    listaNelem_moverse_siguiente ( lista);
    assert(!strcmp(listaNelem_dato_actual(lista), "como"));
    listaNelem_moverse_siguiente ( lista);
    assert(listaNelem_dato_actual(lista) == NULL);

    listaNelem_destruir(lista);

    lista = listaNelem_crear(3,free);
    assert(lista);
    char *texto1, *texto2, *texto3;
    texto1 = malloc(sizeof(char)*10);
    assert(texto1);
    texto2 = malloc(sizeof(char)*10);
    assert(texto2);
    texto3 = malloc(sizeof(char)*10);
    assert(texto3);
    strcpy(texto1,"Hola");
    strcpy(texto2,"Mundo");
    strcpy(texto3,"!");
    listaNelem_agregar(lista,texto1);
    listaNelem_agregar(lista,texto2);
    listaNelem_agregar(lista,texto3);
    assert(!strcmp(listaNelem_dato_actual(lista),"!"));
    listaNelem_destruir(lista);
}