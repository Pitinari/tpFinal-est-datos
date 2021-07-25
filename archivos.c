#define _GNU_SOURCE
#include "archivos.h"
#include "tipos_de_datos/tablahash.h"
#include "contacto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// string_a_unsigned: *char -> unsigned
// Dado un string lo transforma a un unsigned (numero natural)
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

// tablahash_a_lista: TablaHash *Contacto -> void
// Dada una tabla hash y una lista de contactos del tamano de la cantidad
// de posiciones ocupadas en la tabla hash, hace que todos los punteros de 
// la lista apunten a los elementos de la tabla
void tablahash_a_lista (TablaHash tabla, Contacto *listaCont){
	unsigned j = 0;
	for (unsigned i = 0; i < tabla->capacidad ; i++){
		if(tabla->elems[i].dato == NULL || tabla->elems[i].eliminado == true)
			continue;
		listaCont[j++] = tabla->elems[i].dato;
	}
}

// merge: **void int int int FuncionComparadoraMergeSort -> Void
// Une dos sublistas de **arr, la primer sublista es arr[l..m] y la segunda
// sublista es arr[m+1..r]. Une las sublistas dependiendo del orden dado por
// la funcion comparadora
void merge(void **arr, int l, int m, int r, FuncionComparadoraMergeSort comp)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* crea listas temporales */
    void **L, **R;
	L = malloc(sizeof(void *) * n1);
	R = malloc(sizeof(void *) * n2);
 
    /* copia las dos sublistas en L[] y R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Une las dos sublistas dentro de arr[l..r]*/
    i = 0; // Indice inicial de la primera sublista
    j = 0; // Indice inicial de la segunda sublista
    k = l; // Indice inicial de la lista a unir
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
 
    /* Copia los elementos restantes de L[], si es que hay */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copia los elementos restantes de R[], si es que hay */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    //Libera las listas temporales
	free(L);
	free(R);
}
 
// mergeSort: **void int int FuncionComparadoraMergeSort -> Void
// dada una lista, ordena los elementos entre l y r en base a la funcion comparadora
void mergeSort(void **arr, int l, int r, FuncionComparadoraMergeSort comp)
{
    if (l < r) {

        int m = l + (r - l) / 2;
 
        // Corre la funcion recursivamente conz las dos mitades
        mergeSort(arr, l, m, comp);
        mergeSort(arr, m + 1, r, comp);
 
        merge(arr, l, m, r, comp);
    }
}

//cargar: *TablaHash *char -> void
// agrega los elementos de un archivo con formato csv a la tabla hash
void cargar(TablaHash *tabla, char *nombreArchivo){
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
		// si la tabla tiene mas de un 70% ocupado se agranda
		if (((float)tablahash_nelems(*tabla) / (float)tablahash_capacidad(*tabla)) > 0.7)
        	*tabla = tablahash_agrandar(*tabla);

		cont = contacto_crear(parametros[0],parametros[1],string_a_unsigned(parametros[2]),parametros[3]);
		if(cont->edad == 0)
			cont->edad = 1;
    	tablahash_insertar(*tabla, cont); //inserta el contacto en la tabla
    	free(control);
		contacto_eliminar(cont);
		buffer = NULL;
    	free(parametros[2]);
	}

	fclose(archivo);
}

//guardar: *TablaHash *char -> void
// Dada la tabla hash y el nombre de un archivo, guarda todos los elementos de la misma
// en el archivo con formato csv
void guardar(TablaHash *tabla, char *nombreArchivo){
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){ //Si no lo pudo abrir termina
		printf("El archivo no se pudo abrir\n");
		return;
	}
	fprintf(archivo, "nombre,apellido,edad,telefono");
	for (unsigned i = 0; i < tablahash_capacidad(*tabla) ; i++){//pasa por cada elemento
		if ( ((*tabla)->elems[i].dato == NULL) || ((*tabla)->elems[i].eliminado == true) )
			continue; //lo ignora si es null o esta eliminado
		fprintf(archivo, "\n%s,%s,%u,%s", 
		((Contacto)(*tabla)->elems[i].dato)->nombre, ((Contacto)(*tabla)->elems[i].dato)->apellido,
		((Contacto)(*tabla)->elems[i].dato)->edad, ((Contacto)(*tabla)->elems[i].dato)->telefono);
	}	//en caso opuesto lo guarda en el archivo
	fclose(archivo);
}

//guardar_ordenado: *TablaHash *char *char -> void
// Dada la tabla hash, el nombre de un archivo y un argumento, guarda en el archivo
// los contactos ordenados por el respectivo argumento
void guardar_ordenado (TablaHash *tabla, char *nombreArchivo, char *argumento){
	FILE *archivo = fopen(nombreArchivo, "w");
	if (archivo == NULL){//si el archivo no se puede abrir termina
		printf("El archivo no se pudo abrir\n");
		fclose(archivo);
		return;
	}
	
	//crea una lista que va a tener como datos los contactos de la tabla hash
	Contacto *listaCont = malloc(sizeof(Contacto)*((*tabla)->numElems));
	tablahash_a_lista (*tabla,listaCont);

	if (!strcmp(argumento,"nombre")){//ordena por el argumento especificado
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
	//guarda en el archivo todos los contactos ordenados
	fprintf(archivo, "nombre,apellido,edad,telefono");
	for (unsigned i = 0; i < (*tabla)->numElems ; i++){
		fprintf(archivo, "\n%s,%s,%u,%s", 
		listaCont[i]->nombre, listaCont[i]->apellido,
		listaCont[i]->edad, listaCont[i]->telefono);
	}
	fclose(archivo);
	free(listaCont);
}