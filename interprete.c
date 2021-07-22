#include "interprete.h"
#include "contacto.h"
#include "archivos.h"
#include "tipos_de_datos/tablahash.h"

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
  // almacenamos siempre 1 extra de espacio para poder guardar el terminador
  string = realloc(string, sizeof(char)*(tamano+1));
  string[i]='\0';
  return string;
}

void interprete_buscar (TablaHash *tabla){
    char *nombre, *apellido;
    Contacto cont;
    printf("Buscar contacto\nNombre: ");
    nombre = ingresar_buffer();

    printf("Apellido: ");
    apellido = ingresar_buffer();

    Contacto aux = contacto_crear(nombre,apellido,0,NULL);
    cont = (Contacto) tablahash_buscar(*tabla, aux);
    contacto_eliminar(aux);
    contacto_mostrar(cont);
    return;
}

void interprete_agregar (TablaHash *tabla){
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
    return;
}

void interprete_eliminar (TablaHash *tabla){
    char *nombre, *apellido;
    Contacto cont;
    printf("Eliminar contacto\nNombre: ");
    nombre = ingresar_buffer();
    printf("Apellido: ");
    apellido = ingresar_buffer();
    cont = contacto_crear(nombre,apellido,0,NULL);
    tablahash_eliminar(*tabla, cont);
    contacto_eliminar(cont);
    return;
}

void interprete_editar (TablaHash *tabla){
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
        contacto_reemplazar_datos (cont, edad, telefono);
    }
    else
        printf("El contacto no existe\n");
    return;
}

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
    if (*param[0] == '\0' && *param[1] == '\0' && *param[2] == '\0' && *param[3] == '\0'){
        printf("Ningun parametro es no nulo\n");
        for (i=0 ; i<4 ; i++){
            free(param[i]);
        }
        return;
    }
    
    Contacto cont;
    bool noVacio = false;
    for(i=0 ; i < tablahash_capacidad(*tabla) ; i++){
        if ((*tabla)->elems[i].dato == NULL || (*tabla)->elems[i].eliminado == true)
            continue;
        cont = (Contacto)(*tabla)->elems[i].dato;
        if ( !strcmp(cont->nombre,param[0]) &&
             !strcmp(cont->apellido,param[1]) &&
             !strcmp(cont->telefono,param[3]) &&
             (cont->edad == string_a_unsigned(param[2])) ){
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
    if (*param[0] == '\0' && *param[1] == '\0' && *param[2] == '\0' && *param[3] == '\0'){
        printf("Ningun parametro es no nulo\n");
        for (i=0 ; i<4 ; i++){
            free(param[i]);
        }
        return;
    }
    Contacto cont;
    bool noVacio = false;
    for (i=0 ; i < tablahash_capacidad(*tabla) ; i++) {
        if ((*tabla)->elems[i].dato == NULL || (*tabla)->elems[i].eliminado == true)
            continue;
        cont = (Contacto)(*tabla)->elems[i].dato;
        if ( !strcmp(cont->nombre,param[0]) ||
             !strcmp(cont->apellido,param[1]) ||
             !strcmp(cont->telefono,param[3]) ||
             (cont->edad == string_a_unsigned(param[2])) ){
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

//interpreta: *Char TablaHash -> Int
// Recibira un buffer de entrada y decidira que accion tomar y retornara
// un entero dependiendo de si seguir pidiendo entrada
bool interpretar(char *buffer, TablaHash *tabla){
    //buscar
    if (buffer[0] == '1' && buffer[1] == '\0'){
        interprete_buscar(tabla);
        return true;
    }
    //agregar
    if (buffer[0] == '2' && buffer[1] == '\0'){
        interprete_agregar(tabla);
        return true;
    }
    //eliminar
    if (buffer[0] == '3' && buffer[1] == '\0'){
        interprete_eliminar(tabla);
        return true;
    }
    //editar
    if (buffer[0] == '4' && buffer[1] == '\0'){
        interprete_editar(tabla);
        return true;
    }
    //cargar
    if (buffer[0] == '5' && buffer[1] == '\0'){
        printf("Ingrese nombre del archivo a cargar: ");
        char *nombreArchivo = ingresar_buffer();
        cargar(tabla, nombreArchivo);
        free(nombreArchivo);        
        return true;
    }
    //guardar
    if (buffer[0] == '6' && buffer[1] == '\0'){
        printf("Ingrese nombre del archivo a guardar: ");
        char *nombreArchivo = ingresar_buffer();
        guardar(tabla,nombreArchivo);
        free(nombreArchivo);
        return true;
    }
    //deshacer
    if (buffer[0] == '7' && buffer[1] == '\0'){
        printf("comando valido");
        return true;
    }
    //rehacer
    if (buffer[0] == '8' && buffer[1] == '\0'){
        printf("comando valido");
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
        printf("comando valido");
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