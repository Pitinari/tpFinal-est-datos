#include "interprete.h"
#include "constantes.h"
#include "tipos_de_datos/tablahash.h"
#include "tipos_de_datos/pila.h"
#include "tipos_de_datos/listaNelem.h"
#include "contacto.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main (){
    char *buffer;
    bool sigue = true;
    TablaHash tabla = tablahash_crear(TABLA_INI, contacto_comparar, contacto_eliminar, contacto_hash);
    ListaNelem deshacer = listaNelem_crear(CANT_DESHACER,contactoAcc_destruir);
    Pila rehacer = pila_crear();
    while (sigue){
        printf(MENU);
        buffer = ingresar_buffer();
        sigue = interpretar(buffer,&tabla,&deshacer,&rehacer);
        free(buffer);
    }
    return 0;
}