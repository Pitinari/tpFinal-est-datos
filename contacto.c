#include "contacto.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
    if (cont == NULL)
        printf("El contacto no existe\n");
    else
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

bool contacto_validar_nombre (char *nombre){
    for (unsigned i = 0; nombre[i] != '\0'; i++){
        if (nombre[i] < 32 || nombre[i] > 126 || nombre[i] == ',')
            return false;
    }
    return true;
}

bool contacto_validar_telefono (char *telefono){
    for (unsigned i = 0; telefono[i] != '\0'; i++){
        if (!(isdigit(telefono[i]) || telefono[i] == '-' || telefono[i] == '+') || telefono[i] == ',')
            return false;
    }
    return true;
}

Contacto contacto_copiar (Contacto cont){
    char *nombre, *apellido, *telefono;
    unsigned edad = cont->edad;
    nombre = malloc(sizeof(char)*strlen(cont->nombre));
    strcpy(nombre,cont->nombre);
    apellido = malloc(sizeof(char)*strlen(cont->apellido));
    strcpy(apellido,cont->apellido);
    telefono = malloc(sizeof(char)*strlen(cont->telefono));
    strcpy(telefono,cont->telefono);
    return contacto_crear(nombre,apellido,edad,telefono);
}

ContactoAcc contactoAcc_crear (Contacto cont, Accion acc){
    ContactoAcc contAcc = malloc(sizeof(struct _Contacto_Accion));
    contAcc->cont = contacto_copiar(cont);
    contAcc->acc = acc;
    return contAcc;
}

void contactoAcc_destruir (void *contAcc){
    contacto_eliminar( ((ContactoAcc)contAcc)->cont);
    free((ContactoAcc)contAcc);
}