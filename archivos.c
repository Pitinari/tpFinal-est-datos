#define _GNU_SOURCE
#include "archivos.h"
#include "tipos_de_datos/tablahash.h"
#include "contacto.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//cargar: TablaHash *char -> void
// agrega los elementos de un archivo con formato csv a la tabla hash
void cargar(TablaHash tabla, char *nombreArchivo){
	char *palabra, *control, *buffer = NULL;
	FILE *archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL){ //Si no se abrio
		printf("El archivo no se pudo abrir\n");
		return;
	}
	char *parametros[4];
	size_t n = 0;
	unsigned i;
	getline(&buffer,&n,archivo); //toma la primera linea del archivo
	//revisa si tiene el formato que se especifica
	if(strcmp(buffer,"nombre,apellido,edad,telefono\n")){
		free(buffer);
		fclose(archivo);
		return;
	}
	if(buffer)
		free(buffer);
	if (feof(archivo)){ //si el archivo esta vacio no hay datos
		printf("Archivo sin datos\n");
		fclose(archivo);
		return;
	}
	buffer = NULL;
	Contacto cont;
	while (!feof(archivo)){ //repetimos hasta que termine el archivo
		getline(&buffer,&n,archivo); //tomamos otra linea del archivo
		if(buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
		control = buffer;
		i=0;
		while ( (palabra = strsep(&buffer,",")) ){
			//divide la linea en los diferentes parametros
			parametros[i] = malloc(sizeof(char)*(strlen(palabra)+1));
			strcpy(parametros[i++],palabra);
		}
		
		cont = contacto_crear(parametros[0],parametros[1],string_a_unsigned(parametros[2]),parametros[3]);
		if(cont->edad == 0)
			cont->edad = 1;
    	tablahash_insertar(tabla, cont); //inserta el contacto en la tabla
    	free(control);
		contacto_eliminar(cont);
		buffer = NULL;
    	free(parametros[2]);
	}

	fclose(archivo);
}

//guardar: TablaHash *char -> void
// Dada la tabla hash y el nombre de un archivo, guarda todos los elementos de la misma
// en el archivo con formato csv
void guardar(TablaHash tabla, char *nombreArchivo){
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){ //Si no lo pudo abrir termina
		printf("El archivo no se pudo abrir\n");
		return;
	}
	fprintf(archivo, "nombre,apellido,edad,telefono");
	for (unsigned i = 0; i < tablahash_capacidad(tabla) ; i++){//pasa por cada elemento
		if ( (tabla->elems[i].dato == NULL) || (tabla->elems[i].eliminado == true) )
			continue; //lo ignora si es null o esta eliminado
		fprintf(archivo, "\n%s,%s,%u,%s", 
		((Contacto)tabla->elems[i].dato)->nombre, ((Contacto)tabla->elems[i].dato)->apellido,
		((Contacto)tabla->elems[i].dato)->edad, ((Contacto)tabla->elems[i].dato)->telefono);
	}	//en caso opuesto lo guarda en el archivo
	fclose(archivo);
}

//guardar_ordenado: TablaHash *char *char -> void
// Dada la tabla hash, el nombre de un archivo y un argumento, guarda en el archivo
// los contactos ordenados por el respectivo argumento
void guardar_ordenado (TablaHash tabla, char *nombreArchivo, char *argumento){
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){//si el archivo no se puede abrir termina
		printf("El archivo no se pudo abrir\n");
		fclose(archivo);
		return;
	}
	
	//crea una lista que va a tener como datos los contactos de la tabla hash
	Contacto *listaCont = (Contacto*)tablahash_a_lista (tabla);

	if (!strcmp(argumento,"nombre")){//ordena por el argumento especificado
		mergeSort((void**)listaCont,0,tabla->numElems-1,contacto_comparar_nombre);
	}
	else if (!strcmp(argumento,"apellido")){
		mergeSort((void**)listaCont,0,tabla->numElems-1,contacto_comparar_apellido);
	}
	else if (!strcmp(argumento,"telefono")){
		mergeSort((void**)listaCont,0,tabla->numElems-1,contacto_comparar_telefono);
	}
	else if (!strcmp(argumento,"edad")){
		mergeSort((void**)listaCont,0,tabla->numElems-1,contacto_comparar_edad);
	}
	else{
		  printf("Argumento no valido\n");
		  fclose(archivo);
		  free(listaCont);
		  return;
	}
	//guarda en el archivo todos los contactos ordenados
	fprintf(archivo, "nombre,apellido,edad,telefono");
	for (unsigned i = 0; i < tabla->numElems ; i++){
		fprintf(archivo, "\n%s,%s,%u,%s", 
		listaCont[i]->nombre, listaCont[i]->apellido,
		listaCont[i]->edad, listaCont[i]->telefono);
	}
	fclose(archivo);
	free(listaCont);
}