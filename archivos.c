#include "archivo.h"
#include "tablahash.h"
#include "interprete.h"
#include "contacto.h"

#include <stdlib.h>
#include <stdio.h>

void agregar_contacto_por_linea (TablaHash *tabla, char *linea){

}

char *tomar_linea (FILE *archivo){
	int tamano = 10 ,c ,i = 0;
	char *buffer = malloc(sizeof(char) * tamano);
	while ((c = getc(*archivo)) != EOF){
		if (i == tamano-1){
			tamano += 10;
			buffer = realloc(sizeof(char) * tamano);
		}
		if (c == '\n'){
			buffer[i] = '\0';
			return buffer;
		}
		buffer[i++] = c;
	}
	if (i > tamano-1){
		buffer = realloc(sizeof(char) * (tamano + 1));
	}
	buffer[i] = '\0';
	
	return buffer;
}

void cargar(TablaHash *tabla){
	printf("Ingrese nombre del archivo a cargar: ");
	char *buffer = ingresar_buffer();
	FILE *archivo = fopen(buffer, "r");
	if (archivo == NULL){
		printf("El archivo no se pudo abrir");
		exit(EXIT_FAILURE);
	}
	free(buffer);

	buffer = tomar_linea(&archivo);

}