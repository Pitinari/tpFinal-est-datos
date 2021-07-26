#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned hash_principal(char *s);

unsigned hash_secundario(char *s);

unsigned int string_a_unsigned(char *st);

char *strsep(char **stringp, const char *delim);

typedef int (*FuncionComparadoraMergeSort)(void *dato1, void *dato2);

void mergeSort(void **arr, int l, int r, FuncionComparadoraMergeSort comp);

#endif /** __UTILS_H__ */