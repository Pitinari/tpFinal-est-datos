#include "test_contacto.h"
#include "test_hash.h"
#include "test_utils.h"
#include "test_pila.h"
#include "test_listaNelem.h"

#include <stdlib.h>
#include <stdio.h>

int main(){
    test_contacto ();
    puts("test contacto completado");
    test_utils ();
    puts("test utils completado");
    test_tablaHash ();
    puts("test tabla hash completado");
    test_pila ();
    puts("test pila completado");
    test_listaNelem ();
    puts("test Lista de N elementos completado");
    return 0;
}