#include "archivo.h"
#include "tablahash.h"
#include "interprete.h"
#include "contacto.h"

#include <stdlib.h>
#include <stdio.h>

void cargar(TablaHash *tabla){
	printf("Ingrese nombre del archivo a cargar: ");
	char *buffer = ingresar_buffer();
	FILE *archivo = fopen(buffer, "r");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir");
		exit(EXIT_FAILURE);
	}
	free(buffer);



}