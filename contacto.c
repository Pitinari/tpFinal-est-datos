#include "contacto.h"
#include "utilis.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Contacto contacto_crear (char *nombre, char *apellido, unsigned edad, char *telefono){
    Contacto cont = malloc(sizeof(struct _Contacto));
    cont->nombre = nombre;
    cont->apellido = apellido;
    cont->edad = edad;
    cont->telefono = telefono;
    return cont;
}

void contacto_eliminar (Contacto cont){
    if (cont){
            free(cont->nombre);
            free(cont->apellido);
        if (cont->telefono)
            free(cont->telefono);
        free(cont);
    }
}

bool contacto_comparar (Contacto cont1, Contacto cont2){
    if (!strcmp(cont1->nombre, cont2->nombre) && 
        !strcmp(cont1->apellido, cont2->apellido))
        return true;
    return false;
}

void contacto_reemplazar_datos (Contacto cont, unsigned edadNueva, char *telefonoNuevo){
    if(cont->telefono)
        free(cont->telefono);
    cont->edad = edadNueva;
    cont->telefono = telefonoNuevo;
}

void contacto_mostrar (Contacto cont){
    printf("Nombre y Apellido: %s %s\tEdad: %d/tTelefono: %s\n",
    cont->nombre,cont->apellido,cont->edad,cont->telefono);
}

unsigned contacto_hash (Contacto cont, unsigned cantidadColisiones){
    char *key = malloc(sizeof(char)*(strlen(cont->nombre)+strlen(cont->apellido)+2));
    strcat(key,nombre);
    strcat(key,",");
    strcat(key,apellido);
    unsigned hash = hash_principal(key) + (cantidadColisiones * hash_secundario(key));
    free(key);
    return hash;
}