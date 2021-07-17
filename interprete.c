#include "interprete.h"
#include "contacto.h"
#include "tablahash.h"

#include <stdlib.h>
#include <stdio.h>

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

//interpreta: *Char TablaHash -> Int
// Recibira un buffer de entrada y decidira que accion tomar y retornara
// un entero dependiendo de si seguir pidiendo entrada
bool interpretar(char *buffer, TablaHash tabla){
    char *nombre, *apellido;
    Contacto cont;
    //buscar
    if (buffer[0] == '1' && buffer[1] == '\0'){
        printf("Buscar contacto\nNombre: ");
        nombre = ingresar_buffer();
        //validar()
        printf("Apellido: ");
        apellido = ingresar_buffer();
        //validar()
        Contacto aux = contacto_crear(nombre,apellido,0,NULL);
        cont = (Contacto) tablahash_buscar(tabla, aux);
        contacto_eliminar(aux);
        contacto_mostrar(cont);
        return true;
    }
    char *telefono;
    unsigned edad;
    //agregar
    if (buffer[0] == '2' && buffer[1] == '\0'){
        printf("Agregar contacto\nNombre: ");
        nombre = ingresar_buffer();
        //validar()
        printf("Apellido: ");
        apellido = ingresar_buffer();
        //validar()
        printf("Edad: ");
        scanf("%u",&edad);
        getchar();
        //validar()
        printf("Telefono: ");
        telefono = ingresar_buffer();
        //validar()
        cont = contacto_crear(nombre,apellido,edad,telefono);

        //Si la tabla se esta quedando con poco espacio, se agranda
        if (((float)tablahash_nelems(tabla) / (float)tablahash_capacidad(tabla)) > 0.7)
            tabla = tablahash_agrandar(tabla);
        
        tablahash_insertar(tabla, cont);
        return true;
    }
    //eliminar
    if (buffer[0] == '3' && buffer[1] == '\0'){
        printf("Eliminar contacto\nNombre: ");
        
        return true;
    }
    //editar
    if (buffer[0] == '4' && buffer[1] == '\0'){
        printf("comando valido");
        return true;
    }
    //cargar
    if (buffer[0] == '5' && buffer[1] == '\0'){
        printf("comando valido");
        return true;
    }
    //guardar
    if (buffer[0] == '6' && buffer[1] == '\0'){
        printf("comando valido");
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
        printf("comando valido");
        return true;
    }
    //or
    if (buffer[0] == '1' && buffer[1] == '0' && buffer[2] == '\0'){
        printf("comando valido");
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