#include "test_utils.h"
#include "../utils.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

int comparadora (void *dato1, void *dato2){
    return *((int*)dato1) - *((int*)dato2);
}

void test_utils (){
    assert(string_a_unsigned("123") == 123);
    assert(string_a_unsigned("abc") == 0);

    char *control, *buffer = malloc(sizeof(char)*20);
    control = buffer;
    strcpy(buffer,"Hola Mundo");
    assert(buffer);
    char *palabra = strsep(&buffer," ");
    assert(!strcmp(palabra,"Hola"));
    assert(!strcmp(buffer,"Mundo"));
    free(control);
}