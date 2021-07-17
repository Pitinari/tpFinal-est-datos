#include "contacto.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
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

void contacto_eliminar (void *cont){
    if ((Contacto)cont){
            free(((Contacto)cont)->nombre);
            free(((Contacto)cont)->apellido);
        if (((Contacto)cont)->telefono)
            free(((Contacto)cont)->telefono);
        free(((Contacto)cont));
    }
}

bool contacto_comparar (void *cont1,void *cont2){
    if (!strcmp(((Contacto)cont1)->nombre,((Contacto)cont2)->nombre) && 
        !strcmp(((Contacto)cont1)->apellido,((Contacto)cont2)->apellido))
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
    printf("Nombre y Apellido: %s %s\tEdad: %d\tTelefono: %s\n",
    cont->nombre,cont->apellido,cont->edad,cont->telefono);
}

unsigned contacto_hash (void *cont, unsigned cantidadColisiones){
    char *key = malloc(sizeof(char)*(strlen(((Contacto) cont)->nombre)+strlen(((Contacto) cont)->apellido)+2));
    *key = '\0';
    strcat(key,((Contacto) cont)->nombre);
    strcat(key,",");
    strcat(key,((Contacto) cont)->apellido);
    unsigned hash = hash_principal(key) + (cantidadColisiones * hash_secundario(key));
    free(key);
    return hash;
}