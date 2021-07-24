#include "interprete.h"
#include "contacto.h"
#include "archivos.h"
#include "tipos_de_datos/tablahash.h"
#include "tipos_de_datos/listaNelem.h"
#include "tipos_de_datos/pila.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// ingresar_buffer : Nada -> *char
// guarda en memoria un string de largo dinamico, almacenando de a 10
// para que no se utilice realloc en cada caracter
char *ingresar_buffer(){
  int c,i;
  int tamano = 10; 
  char* string = malloc(sizeof(char) * tamano);
  for(i=0;(c=getchar())!='\n'; i++){ //sigue ingresando mientras no sea enter
      if (tamano <= i){
        tamano += 10;
        // realloc de a 10 para no hacerlo en cada iteracion
        string = realloc(string, sizeof(char) * tamano);  
      }
      string[i] = (char) c;
  }
  // almacenamos 1 extra de espacio para poder guardar el terminador
  if (tamano <= i)
    string = realloc(string, sizeof(char)*(tamano+1));
  string[i]='\0';
  return string;
}

//interprete_buscar: **(struct _TablaHash) -> Void
// se encarga de pedir los datos claves del contacto, buscarlo y mostrarlo en pantalla
void interprete_buscar (TablaHash *tabla){
    char *nombre, *apellido;
    Contacto cont;
    printf("Buscar contacto\nNombre: ");
    nombre = ingresar_buffer();

    printf("Apellido: ");
    apellido = ingresar_buffer();

    //busco el contacto en la tabla hash creando un auxiliar
    Contacto aux = contacto_crear(nombre,apellido,0,NULL);
    cont = (Contacto) tablahash_buscar(*tabla, aux);
    //despues lo liberamos y mostramos el resultado de buscar el contacto
    contacto_eliminar(aux);
    contacto_mostrar(cont);
    return;
}

//interprete_agregar: **(struct _TablaHash) -> Void
//Se encarga de pedir los datos para crear un contacto, validarlos y agregarlos
// a la tabla hash
void interprete_agregar (TablaHash *tabla, ListaNelem *deshacer, Pila *rehacer){
    Contacto cont;
    char *nombre, *apellido, *telefono;
    unsigned edad;
    printf("Agregar contacto\nNombre: ");
    nombre = ingresar_buffer();
    if (contacto_validar_nombre(nombre) == false){
        printf("Nombre no valido\n");
        free(nombre);
        return;
    }
    printf("Apellido: ");
    apellido = ingresar_buffer();
    if (contacto_validar_nombre(apellido) == false){
        printf("Apellido no valido\n");
        free(nombre);
        free(apellido);
        return;
    }
    printf("Edad: ");
    scanf("%u",&edad);
    getchar();
    printf("Telefono: ");
    telefono = ingresar_buffer();
    if (contacto_validar_telefono(telefono) == false){
        printf("Telefono no valido\n");
        free(nombre);
        free(apellido);
        free(telefono);
        return;
    }
    cont = contacto_crear(nombre,apellido,edad,telefono);
    //Si la tabla se esta quedando con poco espacio, se agranda
    if (((float)tablahash_nelems(*tabla) / (float)tablahash_capacidad(*tabla)) > 0.7)
        *tabla = tablahash_agrandar(*tabla);

    tablahash_insertar(*tabla, cont);
    listaNelem_agregar (*deshacer, contactoAcc_crear(cont,Eliminar));
    if (*rehacer != NULL){
        pila_destruir(*rehacer, contactoAcc_destruir);
        *rehacer = pila_crear();
    }
    contacto_eliminar(cont);
    return;
}

//interprete_eliminar: **(struct _TablaHash) -> Void
//Pide los campos claves para eliminar un elemento de la tabla hash
void interprete_eliminar (TablaHash *tabla, ListaNelem *deshacer, Pila *rehacer){
    char *nombre, *apellido;

    printf("Eliminar contacto\nNombre: ");
    nombre = ingresar_buffer();
    printf("Apellido: ");
    apellido = ingresar_buffer();
    //Se crea un contacto con los mismos campos claves que el que queremos eliminar
    Contacto cont, aux = contacto_crear(nombre,apellido,0,NULL);
    cont = (Contacto) tablahash_buscar(*tabla, aux);
    if(cont != NULL){
        tablahash_eliminar(*tabla, cont);
        listaNelem_agregar (*deshacer, contactoAcc_crear(cont,Agregar));
        if (*rehacer != NULL){
            pila_destruir(*rehacer, contactoAcc_destruir);
            *rehacer = pila_crear();
        }
    }
    //se elimina y luego se libera el contacto auxiliar
    contacto_eliminar(aux);
    contacto_eliminar(cont);
    return;
}

//interprete_editar: **(struct _TablaHash) -> Void
// Pide los campos claves para buscar un contacto en la tabla hash, si lo
// encuentra pide los campos a modificar y los valida antes de reemplazarlos
void interprete_editar (TablaHash *tabla, ListaNelem *deshacer, Pila *rehacer){
    Contacto cont;
    char *nombre, *apellido, *telefono;
    unsigned edad;
    printf("Editar contacto\nNombre: ");
    nombre = ingresar_buffer();
    printf("Apellido: ");
    apellido = ingresar_buffer();
    Contacto aux = contacto_crear(nombre,apellido,0,NULL);
    cont = (Contacto) tablahash_buscar(*tabla, aux);
    contacto_eliminar(aux);
    //si se encontro un contacto pide el resto de los campos
    if (cont != NULL){
        printf("Edad a reemplazar: ");
        scanf("%u",&edad);
        getchar();
        printf("Telefono a reemplazar: ");
        telefono = ingresar_buffer();
        if (contacto_validar_telefono(telefono) == false){
            printf("Telefono no valido\n");
            free(telefono);
        return;
        }
        //si los campos son validos se reemplazan
        listaNelem_agregar (*deshacer, contactoAcc_crear(cont,Editar));
        if (*rehacer != NULL){
            pila_destruir(*rehacer, contactoAcc_destruir);
            *rehacer = pila_crear();
        }
        contacto_reemplazar_datos (cont, edad, telefono);
    }
    else
        printf("El contacto no existe\n");
    return;
}

//filtrar_and: **(struct _TablaHash) -> Void
//Pide el ingreso de los 4 campos de un contacto y busca dentro de la tabla hash
// cuales contactos cumplen con todos los argumentos no nulos
void filtrar_and(TablaHash *tabla){
    char *param[4];
    printf("Ingresar nombre: ");
    param[0] = ingresar_buffer();
    printf("Ingresar apellido: ");
    param[1] = ingresar_buffer();
    printf("Ingresar edad: ");
    param[2] = ingresar_buffer();
    printf("Ingresar telefono: ");
    param[3] = ingresar_buffer();
    unsigned i;
    //revisa si ningun parametro es no nulo
    if (*param[0] == '\0' && *param[1] == '\0' && *param[2] == '\0' && *param[3] == '\0'){
        printf("Ningun parametro es no nulo\n");
        for (i=0 ; i<4 ; i++){
            free(param[i]);
        }
        return;
    }
    
    Contacto cont;
    bool noVacio = false; //para avisar que ningun contacto cumple con el filtro
    for(i=0 ; i < tablahash_capacidad(*tabla) ; i++){
        if ((*tabla)->elems[i].dato == NULL || (*tabla)->elems[i].eliminado == true)
            continue;
        cont = (Contacto)(*tabla)->elems[i].dato;
        //Revisa 1 por 1 los parametros, si son no nulos los compara con el campo
        // respectivo del contacto actual
        if ( (*param[0] == '\0' ? true : !strcmp(cont->nombre,param[0])) &&
             (*param[1] == '\0' ? true : !strcmp(cont->apellido,param[1])) &&
             (*param[3] == '\0' ? true : !strcmp(cont->telefono,param[3])) &&
             (*param[2] == '\0' ? true : (cont->edad == string_a_unsigned(param[2]))) ){
            contacto_mostrar(cont);
            noVacio = true;
        }
    }
    if (noVacio == false)
        printf("Ningun contacto coincide\n");

    for (i=0 ; i<4 ; i++){
        free(param[i]);
    }
}

//filtrar_or: **(struct _TablaHash) -> Void
//Pide el ingreso de los 4 campos de un contacto y busca dentro de la tabla hash
// cuales contactos cumplen con al menos un argumento no nulo
void filtrar_or(TablaHash *tabla){
    char *param[4];
    printf("Ingresar nombre: ");
    param[0] = ingresar_buffer();
    printf("Ingresar apellido: ");
    param[1] = ingresar_buffer();
    printf("Ingresar edad: ");
    param[2] = ingresar_buffer();
    printf("Ingresar telefono: ");
    param[3] = ingresar_buffer();
    unsigned i;
    //revisa si ningun parametro es no nulo
    if (*param[0] == '\0' && *param[1] == '\0' && *param[2] == '\0' && *param[3] == '\0'){
        printf("Ningun parametro es no nulo\n");
        for (i=0 ; i<4 ; i++){
            free(param[i]);
        }
        return;
    }
    Contacto cont;
    bool noVacio = false; //para avisar que ningun contacto cumple con el filtro
    for (i=0 ; i < tablahash_capacidad(*tabla) ; i++) {
        if ((*tabla)->elems[i].dato == NULL || (*tabla)->elems[i].eliminado == true)
            continue;
        cont = (Contacto)(*tabla)->elems[i].dato;
        // si el argumento es no nulo lo compara con el respectivo parametro del contacto 
        if ( (*param[0] == '\0' ? false : !strcmp(cont->nombre,param[0])) ||
             (*param[1] == '\0' ? false : !strcmp(cont->apellido,param[1])) ||
             (*param[3] == '\0' ? false : !strcmp(cont->telefono,param[3])) ||
             (*param[2] == '\0' ? false : (cont->edad == string_a_unsigned(param[2]))) ){
            contacto_mostrar(cont);
            noVacio = true;
        }
    }
    if (noVacio == false)
        printf("Ningun contacto coincide\n");
    
    for (i=0 ; i<4 ; i++){
        free(param[i]);
    }
}

void interprete_deshacer (TablaHash *tabla, ListaNelem *deshacer, Pila *rehacer){
    ContactoAcc contAcc = (ContactoAcc)listaNelem_dato_actual(*deshacer);
    if (contAcc == NULL){
        printf("No hay nada que deshacer\n");
        return;
    }
    else if (contAcc->acc == Agregar){
        *rehacer = pila_agregar(*rehacer, contactoAcc_crear(contAcc->cont,Eliminar));
        tablahash_insertar(*tabla, contAcc->cont);
    }
    else if (contAcc->acc == Eliminar){
        *rehacer = pila_agregar(*rehacer, contactoAcc_crear(contAcc->cont,Agregar));
        tablahash_eliminar(*tabla, contAcc->cont);
    }
    else if (contAcc->acc == Editar){
        Contacto cont = (Contacto) tablahash_buscar(*tabla, contAcc->cont);
        *rehacer = pila_agregar(*rehacer, contactoAcc_crear(cont,Editar));
        contacto_reemplazar_datos (cont, contAcc->cont->edad, contAcc->cont->telefono);
    }
    listaNelem_moverse_siguiente (*deshacer);
}

void interprete_rehacer (TablaHash *tabla, ListaNelem *deshacer, Pila *rehacer){
    ContactoAcc contAcc = (ContactoAcc)pila_primero(*rehacer);
    if (contAcc == NULL){
        printf("No hay nada que rehacer\n");
        return;
    }
    else if (contAcc->acc == Agregar){
        listaNelem_agregar(*deshacer, contactoAcc_crear(contAcc->cont,Eliminar));
        tablahash_insertar(*tabla, contAcc->cont);
    }
    else if (contAcc->acc == Eliminar){
        listaNelem_agregar(*deshacer, contactoAcc_crear(contAcc->cont,Agregar));
        tablahash_eliminar(*tabla, contAcc->cont);
    }
    else if (contAcc->acc == Editar){
        Contacto cont = (Contacto) tablahash_buscar(*tabla, contAcc->cont);
        listaNelem_agregar(*deshacer, contactoAcc_crear(cont,Editar));
        contacto_reemplazar_datos (cont, contAcc->cont->edad, contAcc->cont->telefono);
    }
    *rehacer = pila_borrar_primero (*rehacer,contactoAcc_destruir);
}

//interpreta: *Char TablaHash -> Int
// Recibira un buffer de entrada y decidira que accion tomar y retornara
// un entero dependiendo de si seguir pidiendo entrada
bool interpretar(char *buffer, TablaHash *tabla, ListaNelem *deshacer, Pila *rehacer){
    //buscar
    if (buffer[0] == '1' && buffer[1] == '\0'){
        interprete_buscar(tabla);
        return true;
    }
    //agregar
    if (buffer[0] == '2' && buffer[1] == '\0'){
        interprete_agregar(tabla,deshacer,rehacer);
        return true;
    }
    //eliminar
    if (buffer[0] == '3' && buffer[1] == '\0'){
        interprete_eliminar(tabla,deshacer,rehacer);
        return true;
    }
    //editar
    if (buffer[0] == '4' && buffer[1] == '\0'){
        interprete_editar(tabla,deshacer,rehacer);
        return true;
    }
    //cargar
    if (buffer[0] == '5' && buffer[1] == '\0'){
        printf("Ingrese ruta del archivo a cargar: ");
        char *nombreArchivo = ingresar_buffer();
        cargar(tabla, nombreArchivo);
        free(nombreArchivo);        
        return true;
    }
    //guardar
    if (buffer[0] == '6' && buffer[1] == '\0'){
        printf("Ingrese ruta del archivo a guardar: ");
        char *nombreArchivo = ingresar_buffer();
        guardar(tabla,nombreArchivo);
        free(nombreArchivo);
        return true;
    }
    //deshacer
    if (buffer[0] == '7' && buffer[1] == '\0'){
        interprete_deshacer(tabla,deshacer,rehacer);
        return true;
    }
    //rehacer
    if (buffer[0] == '8' && buffer[1] == '\0'){
        interprete_rehacer(tabla,deshacer,rehacer);
        return true;
    }
    //and
    if (buffer[0] == '9' && buffer[1] == '\0'){
        filtrar_and(tabla);
        return true;
    }
    //or
    if (buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '\0'){
        filtrar_or(tabla);
        return true;
    }
    //guardar ordenado
    if (buffer[0] == '1' && buffer[1] == '1' && buffer[2] == '\0'){
        char *nombreArchivo, *argumento;
        printf("Ingrese ruta del archivo a guardar: ");
        nombreArchivo = ingresar_buffer();
        printf("Ingrese nombre de atributo: ");
        argumento = ingresar_buffer();
        guardar_ordenado (tabla, nombreArchivo, argumento);
        free(nombreArchivo);
        free(argumento);
        return true;
    }
    //buscar por suma de edades
    if (buffer[0] == '1' && buffer[1] == '2' && buffer[2] == '\0'){
        printf("comando valido");
        return true;
    }
    //salir
    if (buffer[0] == '1' && buffer[1] == '3' && buffer[2] == '\0'){
        return false;
    }
    //error en la entrada
    else{
        printf("Comando invalido");
        return true;
    }
}