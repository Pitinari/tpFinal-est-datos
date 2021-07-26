#include "interprete.h"
#include "constantes.h"
#include "contacto.h"
#include "tipos_de_datos/tablahash.h"
#include "tipos_de_datos/pila.h"
#include "tipos_de_datos/listaNelem.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main (){
    char *buffer;
    //inicializacion de variables
    bool sigue = true;
    TablaHash tabla = tablahash_crear(TABLA_INI, contacto_comparar, contacto_eliminar, contacto_hash, contacto_copiar);
    ListaNelem deshacer = listaNelem_crear(CANT_DESHACER,contactoAcc_destruir);
    Pila rehacer = pila_crear();
    
    //bucle programa
    while (sigue){
        printf(MENU);
        buffer = ingresar_buffer();
        sigue = interpretar(buffer,tabla,deshacer,&rehacer);
        free(buffer);
    }

    //final, liberar memoria
    tablahash_destruir(tabla);
    listaNelem_destruir(deshacer);
    pila_destruir(rehacer,contactoAcc_destruir);
    return 0;
}