#include "archivos.h"
#include "tipos_de_datos/tablahash.h"
#include "contacto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned int string_a_unsigned(char *st) {
  char *x;
  for (x = st ; *x ; x++) {
    if (!isdigit(*x))
      return 0L;
  }
  return (strtoul(st, 0L, 10));
}

void cargar(TablaHash *tabla, char *nombreArchivo){
	char *palabra, *control, *buffer;
	FILE *archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir");
		exit(EXIT_FAILURE);
	}
	char *parametros[4];
	unsigned i;
	while (getline(&buffer,NULL,archivo) == -1){
		buffer[strlen(buffer)-1] = '\0';
		control = buffer;
		i=0;
		while (palabra = strsep(&buffer,",")){
			parametros[i] = malloc(sizeof(char)*strlen(palabra));
			strcpy(parametros[i++],palabra);
		}
		if (((float)tablahash_nelems(*tabla) / (float)tablahash_capacidad(*tabla)) > 0.7)
        	*tabla = tablahash_agrandar(*tabla);

    	tablahash_insertar(*tabla, contacto_crear(parametros[1],parametros[2],string_a_unsigned(parametros[3]),parametros[4]));
    	free(control);
    	free(parametros[3]);
	}
	fclose(archivo);
}

void guardar(TablaHash *tabla, char *nombreArchivo){
	printf("Ingrese nombre del archivo a guardar: ");
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir");
		exit(EXIT_FAILURE);
	}
	fprintf(archivo, "nombre,apellido,edad,telefono\n");
	for (unsigned i = 0; i < tablahash_capacidad(*tabla) ; i++){
		if ( ((*tabla)->elems[i].dato == NULL) || ((*tabla)->elems[i].eliminado == true) )
			continue;
		fprintf(archivo, "%s,%s,%u,%s\n", 
		((Contacto)(*tabla)->elems[i].dato)->nombre, ((Contacto)(*tabla)->elems[i].dato)->apellido,
		((Contacto)(*tabla)->elems[i].dato)->edad, ((Contacto)(*tabla)->elems[i].dato)->telefono);
	}
	fclose(archivo);
}