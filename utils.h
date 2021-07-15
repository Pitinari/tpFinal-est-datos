#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned hash_principal(char *s);

unsigned hash_secundario(char *s);

#endif /** __UTILS_H__ */