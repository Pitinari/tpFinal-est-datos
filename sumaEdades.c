#include "contacto.h"
#include "sumaEdades.h"
#include "tipos_de_datos/pila.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//generar_tabla_sumaEdades: *Contacto Unsigned Unsigned -> **bool
/*
 Pensando la lista de contactos como la lista de las edades. La funcion
 crea una matriz de booleanos del tamaño de la cantidad de contactos + 1 por
 el valor de la de suma + 1 al que queremos llegar, entonces la matriz de booleanos
 en B[i][j] es true si existe alguna combinacion de edades entre Edades[0...i]
 que sume el valor j, razonandolo de la siguiente manera:
 if (Edades[i-1] > j)
    B[i][j] = B[i-1][j]
 else 
    B[i][j] = B[i-1][j] OR B[i-1][j-Edades[i-1]]
 eso nos dice que si en B[cantidad contactos][suma buscada] es true, entonces existe
 una combinacion en edades igual a la suma buscada
*/
bool **generar_tabla_sumaEdades (Contacto *contactos, unsigned cantContactos, unsigned suma){
    //inicia declarando la tabla que vamos a devolver
    bool **tabla = malloc(sizeof(bool*)*(cantContactos+1));
    unsigned i,j;
    //mientras termina de inicializarla, llena los casos bases
    //si la suma buscada es 0, todos son true
    for (i = 0; i <= cantContactos; i++){
        tabla[i] = malloc(sizeof(bool)*(suma+1));
        tabla[i][0] = true;
    }
    //mientras que para todos los posibles valores de suma, no
    //podremos formarlo con el contacto base (edad 0)
    for (i = 1; i <= suma; i++)
        tabla[0][i] = false;
    
    for (i=1 ; i <= cantContactos ; i++){
        for (j=1 ; j <= suma ; j++){
            if(j < contactos[i-1]->edad)
                tabla[i][j] = tabla[i-1][j];
            else
                tabla[i][j] = (tabla[i-1][j] || tabla[i-1][j-(contactos[i-1]->edad)]);
        }
    }
    return tabla;
}

//destruir_tabla_sumaEdades: **bool Unsigned -> void
//libera memoria de una matriz de booleanos
void destruir_tabla_sumaEdades (bool **tabla, unsigned cantContactos){
    for (unsigned i = 0 ; i <= cantContactos ; i++)
        free(tabla[i]);
    free(tabla);
}

Pila subconjunto_contactos_suma(bool **tabla, Contacto *contactos, unsigned cantContactos, unsigned suma){
    Pila contSum = pila_crear();
    for (unsigned i = cantContactos, j = suma; i>0 && j>0; i--){
        if (tabla[i-1][j] == false){ //significa que el contacto actual sirve para la suma
            contSum = pila_agregar(contSum, contactos[i-1]);
            //se agrega el contacto actual a la pila (i-1 ya que la tabla tiene los casos base)
            j -= contactos[i-1]->edad;
            //se resta la edad del contacto agregado al valor suma para buscar
            //el siguiente contacto que sirva para formar j
        }
        //en caso de que el contacto actual no afecte a la suma, lo saltea
    }
    return contSum;
}