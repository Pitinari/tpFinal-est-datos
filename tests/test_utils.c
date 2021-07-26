#include "test_utils.h"
#include "../utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int comparadora (void *dato1, void *dato2){
    return *((int*)dato2) - *((int*)dato1);
}

void test_utils (){
    //string_a_unsigned
    assert(string_a_unsigned("123") == 123);
    assert(string_a_unsigned("abc") == 0);

    //strsep
    char *control, *buffer = malloc(sizeof(char)*20);
    assert(buffer);
    control = buffer;
    strcpy(buffer,"Hola Mundo");
    assert(buffer);
    char *palabra = strsep(&buffer," ");
    assert(!strcmp(palabra,"Hola"));
    assert(!strcmp(buffer,"Mundo"));
    free(control);

    //mergeSort
    int **lista = malloc(sizeof(int*)*6);
    for(unsigned i = 0 ; i<6 ; i++){
        lista[i] = malloc(sizeof(int));
        assert(lista[i]);
    }
    *lista[0] = 2;
    *lista[1] = 7;
    *lista[2] = 9;
    *lista[3] = 10;
    *lista[4] = 4;
    *lista[5] = 6;

    mergeSort((void**)lista,0,5,comparadora);

    assert(*lista[0] == 2);
    assert(*lista[1] == 4);
    assert(*lista[2] == 6);
    assert(*lista[3] == 7);
    assert(*lista[4] == 9);
    assert(*lista[5] == 10);

    for(unsigned i = 0 ; i<6 ; i++)
        free(lista[i]);
    free(lista);

}