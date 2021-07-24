#define _GNU_SOURCE
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

// strsep : **char -> *char -> *char
// Toma la direccion de memoria de un puntero de char y si aparece
// dentro del string, dado por el puntero al que apunta la direccion de 
// memoria del primer parametro, el string del segundo parametro, la funcion
// devuelve el primer string hasta la aparicion del segundo string, y mueve la
// memoria del primer parametro hasta despues de la primera aparicion del
// segundo parametro
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

void cargar(TablaHash *tabla, char *nombreArchivo){
	char *palabra, *control, *buffer = NULL;
	FILE *archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir");
		exit(EXIT_FAILURE);
	}
	char *parametros[4];
	size_t n = 0;
	unsigned i;
	getline(&buffer,&n,archivo);
	if(buffer)
		free(buffer);
	if (feof(archivo)){
		printf("Archivo sin datos");
		return;
	}
	buffer = NULL;
	while (!feof(archivo)){
		getline(&buffer,&n,archivo);
		if(buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
		control = buffer;
		i=0;
		while ( (palabra = strsep(&buffer,",")) ){
			parametros[i] = malloc(sizeof(char)*strlen(palabra));
			strcpy(parametros[i++],palabra);
		}
		if (((float)tablahash_nelems(*tabla) / (float)tablahash_capacidad(*tabla)) > 0.7)
        	*tabla = tablahash_agrandar(*tabla);

    	tablahash_insertar(*tabla, contacto_crear(parametros[0],parametros[1],string_a_unsigned(parametros[2]),parametros[3]));
    	free(control);
		buffer = NULL;
    	free(parametros[2]);
	}

	fclose(archivo);
}

void guardar(TablaHash *tabla, char *nombreArchivo){
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