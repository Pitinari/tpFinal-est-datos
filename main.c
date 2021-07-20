#include "interprete.h"
#include "constantes.h"
#include "tablahash.h"
#include "contacto.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main (){
    char *buffer;
    bool sigue = true;
    TablaHash tabla = tablahash_crear(TABLA_INI, contacto_comparar, contacto_eliminar, contacto_hash);
    while (sigue){
        printf(MENU);
        buffer = ingresar_buffer();
        sigue = interpretar(buffer,&tabla);
        free(buffer);
    }
    return 0;
}