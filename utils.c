#include "utils.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned hash_principal(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 89 * hashval;
  }
  return hashval;
}

unsigned hash_secundario(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; ++s) {
    hashval = *s + 83 * hashval;
  }
  return hashval;
}

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