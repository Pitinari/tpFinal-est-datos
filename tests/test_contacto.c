#include "test_contacto.h"
#include "../contacto.h"
#include "../utils.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void test_contacto (){
	char *nombre, *apellido, *telefono;
	nombre = malloc(sizeof(char)*15);
	apellido = malloc(sizeof(char)*15);
	telefono = malloc(sizeof(char)*15);
	strcpy(nombre,"Pedro");
	strcpy(apellido,"Casado");
	strcpy(telefono,"123456");
	Contacto cont1 = contacto_crear(nombre,apellido,12,telefono);
	assert(cont1);

	nombre = malloc(sizeof(char)*15);
	apellido = malloc(sizeof(char)*15);
	telefono = malloc(sizeof(char)*15);
	strcpy(nombre,"Eduardo");
	strcpy(apellido,"Sosa");
	strcpy(telefono,"654321");
	Contacto cont2 = contacto_crear(nombre,apellido,12,telefono);

	contacto_reemplazar_datos (cont2, 45, "789456");
	assert(cont2);

	assert(contacto_comparar(cont1,cont2) == false);

	assert(contacto_hash(cont1 , 0) != contacto_hash(cont1 , 1));

	assert(contacto_validar_nombre("hol,a") == false);
	assert(contacto_validar_nombre("hoLa") == true);

	assert(contacto_validar_telefono("1324a12") == false);
	assert(contacto_validar_telefono("+54 0341-4532525") == true);

	contacto_eliminar(cont1);
	cont1 = (Contacto)contacto_copiar(cont2);

	assert(contacto_comparar(cont1,cont2) == true);
	assert(contacto_comparar_nombre(cont1,cont2) == 0);
	assert(contacto_comparar_apellido(cont1,cont2) == 0);
	assert(contacto_comparar_telefono(cont1,cont2) == 0);
	assert(contacto_comparar_edad(cont1,cont2) == 0);

	ContactoAcc aux = contactoAcc_crear(cont1,Eliminar);
	assert(aux);
	contactoAcc_destruir(aux);
	contacto_eliminar(cont1);
	contacto_eliminar(cont2);
}