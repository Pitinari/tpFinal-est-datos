#include "contacto.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//contacto_crear: *char *char unsigned *char -> Contacto
//Dados todos los argumentos de un contacto crea una estructura con los parametros
// de la funcion y retorna un puntero a la misma
Contacto contacto_crear (char *nombre, char *apellido, unsigned edad, char *telefono){
    Contacto cont = malloc(sizeof(struct _Contacto));
    cont->nombre = nombre;
    cont->apellido = apellido;
    cont->edad = edad;
    cont->telefono = telefono;
    return cont;
}

//contacto_eliminar: *void -> void
// Recibe un puntero de tipo void que apunta a una estructura de contacto
// y libera la memoria de la misma
void contacto_eliminar (void *cont){
    if ((Contacto)cont){
            free(((Contacto)cont)->nombre);
            free(((Contacto)cont)->apellido);
        if (((Contacto)cont)->telefono)
            free(((Contacto)cont)->telefono);
        free(((Contacto)cont));
    }
}

//contacto_comparar: *void *void -> bool
//Recibe dos punteros de tipo void que apuntan a una estructuta de contacto
// y las compara, si sus valores clave son iguales retorna true, sino false
bool contacto_comparar (void *cont1,void *cont2){
    if (!strcmp(((Contacto)cont1)->nombre,((Contacto)cont2)->nombre) && 
        !strcmp(((Contacto)cont1)->apellido,((Contacto)cont2)->apellido))
        return true;
    return false;
}

//contacto_reemplazar_datos: Contacto unsigned *char -> void
//Dado un contacto, la funcion reemplaza los datos no claves por los recibidos
void contacto_reemplazar_datos (Contacto cont, unsigned edadNueva, char *telefonoNuevo){
    if(cont->telefono)
        free(cont->telefono);
    cont->edad = edadNueva;
    cont->telefono = telefonoNuevo;
}

//contacto_mostrar: Contacto -> void
// Recibe un contacto y muestra sus datos en pantalla
void contacto_mostrar (Contacto cont){
    if (cont == NULL) //en caso de que se NULL quiere decir que no existe
        printf("El contacto no existe\n");
    else
        printf("Nombre y Apellido: %s %s\tEdad: %d\tTelefono: %s\n",
        cont->nombre,cont->apellido,cont->edad,cont->telefono);
}

//contacto_hash: *void unsgined -> unsigned
// Recibe un puntero void que apunta a una estructura de contacto y un argumento natural
// que hace referencia a la cantidad de veces que colisiono el dato con otro hash,
// devuelve un numero natural que es su hash en la tabla hash
unsigned contacto_hash (void *cont, unsigned cantidadColisiones){
    char *key = malloc(sizeof(char)*(strlen(((Contacto) cont)->nombre)+strlen(((Contacto) cont)->apellido)+2));
    *key = '\0';
    strcat(key,((Contacto) cont)->nombre);
    strcat(key,",");
    strcat(key,((Contacto) cont)->apellido);
    //Usa como clave el "nombre,apellido", usando la coma como separador de argumentos
    unsigned hash = hash_principal(key) + (cantidadColisiones * hash_secundario(key));
    free(key);
    return hash;
}

//contacto_validar_nombre: *char -> bool
// Toma un string y corrobora que los caracteres sean validos para guardarlos como nombre
bool contacto_validar_nombre (char *nombre){
    for (unsigned i = 0; nombre[i] != '\0'; i++){
        if (nombre[i] < 32 || nombre[i] > 126 || nombre[i] == ',')
            return false;
    }
    return true;
}

//contacto_validar_telefono: *char -> bool
// Toma un string y corrobora que los caracteres sean validos para guardarlos como telefono
bool contacto_validar_telefono (char *telefono){
    for (unsigned i = 0; telefono[i] != '\0'; i++){
        if (!(isdigit(telefono[i]) || telefono[i] == '-' || telefono[i] == '+') || telefono[i] == ',')
            return false;
    }
    return true;
}

//contacto_copiar: *void -> *void
// Dado un puntero void que apunta a una estructura de contacto y retorna otro puntero
// void que apunta a una copia de la estructura contacto
void *contacto_copiar (void *cont){
    char *nombre, *apellido, *telefono;
    unsigned edad = ((Contacto)cont)->edad;
    nombre = malloc(sizeof(char)*strlen(((Contacto)cont)->nombre)+1);
    strcpy(nombre,((Contacto)cont)->nombre);
    apellido = malloc(sizeof(char)*strlen(((Contacto)cont)->apellido)+1);
    strcpy(apellido,((Contacto)cont)->apellido);
    telefono = malloc(sizeof(char)*strlen(((Contacto)cont)->telefono)+1);
    strcpy(telefono,((Contacto)cont)->telefono);
    return (void*)contacto_crear(nombre,apellido,edad,telefono);
}

//contactoAcc_crear: Contacto Accion -> ContactoAcc
// crea una estructura de ContactoAccion, que indica que accion
// (agregar,eliminar,editar) hacer con un contacto en la tabla hash
ContactoAcc contactoAcc_crear (Contacto cont, Accion acc){
    ContactoAcc contAcc = malloc(sizeof(struct _Contacto_Accion));
    contAcc->cont = contacto_copiar(cont);
    contAcc->acc = acc;
    return contAcc;
}

//contactoAcc_destruir: *void -> void
//libera la memoria de la estructura de ContactoAccion
void contactoAcc_destruir (void *contAcc){
    contacto_eliminar( ((ContactoAcc)contAcc)->cont);
    free((ContactoAcc)contAcc);
}

//Las siguientes son funciones comparadoras que devuelven un numero positivo, negativo
//si son diferentes y 0 si son iguales. Sus parametros son punteros void que apuntan a 
//estructuras Contacto

//contacto_comparar_nombre: *void *void -> int
int contacto_comparar_nombre(void *dato1, void* dato2){
    return strcmp(((Contacto)dato2)->nombre , ((Contacto)dato1)->nombre);
}

//contacto_comparar_nombre: *void *void -> int
int contacto_comparar_apellido(void *dato1, void* dato2){
    return strcmp(((Contacto)dato2)->apellido , ((Contacto)dato1)->apellido);
}

//contacto_comparar_nombre: *void *void -> int
int contacto_comparar_telefono(void *dato1, void* dato2){
    return strcmp(((Contacto)dato2)->telefono , ((Contacto)dato1)->telefono);
}

//contacto_comparar_nombre: *void *void -> int
int contacto_comparar_edad(void *dato1, void* dato2){
    return ((Contacto)dato1)->edad - ((Contacto)dato2)->edad;
}