#include "interprete.h"
#include "constantes.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int main () {
    char *buffer;
    bool sigue = true;
    while (sigue){
        printf(MENU);
        buffer = ingresar_buffer();
        sigue = interpretar(buffer);
        free(buffer);
        printf("Aprete cualquier tecla...");
        getchar();
        system("clear");

    }
    return 0;
}