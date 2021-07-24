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

void tablahash_a_lista (TablaHash tabla, Contacto *listaCont){
	unsigned j = 0;
	for (unsigned i = 0; i < tabla->capacidad ; i++){
		if(tabla->elems[i].dato == NULL || tabla->elems[i].eliminado == true)
			continue;
		listaCont[j++] = tabla->elems[i].dato;
	}
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(void **arr, int l, int m, int r, FuncionComparadoraMergeSort comp)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    void **L, **R;
	L = malloc(sizeof(void *) * n1);
	R = malloc(sizeof(void *) * n2);
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (comp(L[i] , R[j]) > 0) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
	free(L);
	free(R);
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(void **arr, int l, int r, FuncionComparadoraMergeSort comp)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m, comp);
        mergeSort(arr, m + 1, r, comp);
 
        merge(arr, l, m, r, comp);
    }
}

void cargar(TablaHash *tabla, char *nombreArchivo){
	char *palabra, *control, *buffer = NULL;
	FILE *archivo = fopen(nombreArchivo, "r");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir\n");
		return;
	}
	char *parametros[4];
	size_t n = 0;
	unsigned i;
	getline(&buffer,&n,archivo);
	if(strcmp(buffer,"nombre,apellido,edad,telefono\n")){
		free(buffer);
		fclose(archivo);
		return;
	}
	if(buffer)
		free(buffer);
	if (feof(archivo)){
		printf("Archivo sin datos\n");
		fclose(archivo);
		return;
	}
	buffer = NULL;
	Contacto cont;
	while (!feof(archivo)){
		getline(&buffer,&n,archivo);
		if(buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
		control = buffer;
		i=0;
		while ( (palabra = strsep(&buffer,",")) ){
			parametros[i] = malloc(sizeof(char)*(strlen(palabra)+1));
			strcpy(parametros[i++],palabra);
		}
		if (((float)tablahash_nelems(*tabla) / (float)tablahash_capacidad(*tabla)) > 0.7)
        	*tabla = tablahash_agrandar(*tabla);

		
		cont = contacto_crear(parametros[0],parametros[1],string_a_unsigned(parametros[2]),parametros[3]);
    	tablahash_insertar(*tabla, cont);
    	free(control);
		contacto_eliminar(cont);
		buffer = NULL;
    	free(parametros[2]);
	}

	fclose(archivo);
}

void guardar(TablaHash *tabla, char *nombreArchivo){
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir\n");
		return;
	}
	fprintf(archivo, "nombre,apellido,edad,telefono");
	for (unsigned i = 0; i < tablahash_capacidad(*tabla) ; i++){
		if ( ((*tabla)->elems[i].dato == NULL) || ((*tabla)->elems[i].eliminado == true) )
			continue;
		fprintf(archivo, "\n%s,%s,%u,%s", 
		((Contacto)(*tabla)->elems[i].dato)->nombre, ((Contacto)(*tabla)->elems[i].dato)->apellido,
		((Contacto)(*tabla)->elems[i].dato)->edad, ((Contacto)(*tabla)->elems[i].dato)->telefono);
	}
	fclose(archivo);
}

void guardar_ordenado (TablaHash *tabla, char *nombreArchivo, char *argumento){
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir\n");
		fclose(archivo);
		return;
	}
	
	Contacto *listaCont = malloc(sizeof(Contacto)*((*tabla)->numElems));
	tablahash_a_lista (*tabla,listaCont);

	if (!strcmp(argumento,"nombre")){
		mergeSort((void**)listaCont,0,(*tabla)->numElems-1,contacto_comparar_nombre);
	}
	else if (!strcmp(argumento,"apellido")){
		mergeSort((void**)listaCont,0,(*tabla)->numElems-1,contacto_comparar_apellido);
	}
	else if (!strcmp(argumento,"telefono")){
		mergeSort((void**)listaCont,0,(*tabla)->numElems-1,contacto_comparar_telefono);
	}
	else if (!strcmp(argumento,"edad")){
		mergeSort((void**)listaCont,0,(*tabla)->numElems-1,contacto_comparar_edad);
	}
	else{
		  printf("Argumento no valido\n");
		  fclose(archivo);
		  free(listaCont);
		  return;
	}
	fprintf(archivo, "nombre,apellido,edad,telefono");
	for (unsigned i = 0; i < tablahash_capacidad(*tabla) ; i++){
		fprintf(archivo, "\n%s,%s,%u,%s", 
		listaCont[i]->nombre, listaCont[i]->apellido,
		listaCont[i]->edad, listaCont[i]->telefono);
	}
	fclose(archivo);
	free(listaCont);
}