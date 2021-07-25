FLAGS = -Wall -Wextra -Werror -std=c99 -g
DT = tipos_de_datos/

#declaracion de destinos
main: main.o interprete.o contacto.o utils.o archivos.o sumaEdades.o tablahash.o pila.o listaNelem.o
	gcc $(FLAGS) -o $@.out $@.o interprete.o contacto.o utils.o sumaEdades.o archivos.o tablahash.o pila.o listaNelem.o -lm

main.o:	main.c  interprete.h contacto.h $(DT)tablahash.h $(DT)pila.h $(DT)listaNelem.h
	gcc $(FLAGS) -c	main.c

interprete.o: interprete.c interprete.h contacto.h sumaEdades.h $(DT)tablahash.h $(DT)pila.h $(DT)listaNelem.h
	gcc $(FLAGS) -c interprete.c

sumaEdades.o: sumaEdades.c sumaEdades.h contacto.h
	gcc $(FLAGS) -c sumaEdades.c

archivos.o: archivos.c archivos.h $(DT)tablahash.h
	gcc $(FLAGS) -c archivos.c

contacto.o: contacto.c contacto.h utils.h
	gcc $(FLAGS) -c contacto.c

utilis.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c

tablahash.o: $(DT)tablahash.c $(DT)tablahash.h
	gcc $(FLAGS) -c $(DT)tablahash.c -lm

pila.o: $(DT)pila.c $(DT)pila.h
	gcc -c $(DT)pila.c

listaNelem.o: $(DT)listaNelem.c $(DT)listaNelem.h
	gcc -c $(DT)listaNelem.c

clean:
	rm *.o
	rm *.out