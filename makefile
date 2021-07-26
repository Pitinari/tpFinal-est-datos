FLAGS = -Wall -Wextra -Werror -std=c99 -g
DT = tipos_de_datos/
T = tests/

#declaracion de destinos
main: main.o interprete.o contacto.o utils.o archivos.o sumaEdades.o tablahash.o pila.o listaNelem.o
	gcc $(FLAGS) -o $@.out $@.o interprete.o contacto.o utils.o sumaEdades.o archivos.o tablahash.o pila.o listaNelem.o -lm

test: $(T)test.o $(T)test_contacto.o $(T)test_hash.o $(T)test_utils.o $(T)test_pila.o $(T)test_listaNelem.o tablahash.o contacto.o utils.o pila.o listaNelem.o
	gcc $(FLAGS) -o $@.out $(T)test.o $(T)test_contacto.o $(T)test_hash.o $(T)test_utils.o $(T)test_pila.o $(T)test_listaNelem.o tablahash.o contacto.o utils.o pila.o listaNelem.o -lm

test.o: $(T)test.c $(T)test_contacto.h $(T)test_hash.h $(T)test_utils.h $(T)test_pila.h
	gcc $(FLAGS) -c $(T)test.c

test_hash.o: $(T)test_hash.c $(T)test_hash.h $(DT)tablahash.h contacto.h utils.h
	gcc $(FLAGS) -c $(T)test_hash.c -lm

test_pila.o: $(T)test_pila.c $(T)test_pila.h pila.h
	gcc $(FLAGS) -c $(T)test_pila.c

test_listaNelem.o: $(T)test_listaNelem.c $(T)test_listaNelem.h listaNelem.h
	gcc $(FLAGS) -c $(T)test_listaNelem.c

test_contacto.o: $(T)test_contacto.c $(T)test_contacto.h contacto.h utils.h
	gcc $(FLAGS) -c $(T)test_contacto.c

test_utils.o: $(T)test_utils.c $(T)test_utils.h utils.h
	gcc $(FLAGS) -c $(T)test_utils.c

main.o:	main.c  interprete.h contacto.h $(DT)tablahash.h $(DT)pila.h $(DT)listaNelem.h
	gcc $(FLAGS) -c	main.c

interprete.o: interprete.c interprete.h contacto.h sumaEdades.h utils.h $(DT)tablahash.h $(DT)pila.h $(DT)listaNelem.h
	gcc $(FLAGS) -c interprete.c

sumaEdades.o: sumaEdades.c sumaEdades.h contacto.h
	gcc $(FLAGS) -c sumaEdades.c

archivos.o: archivos.c archivos.h utils.h $(DT)tablahash.h
	gcc $(FLAGS) -c archivos.c

contacto.o: contacto.c contacto.h utils.h
	gcc $(FLAGS) -c contacto.c

utils.o: utils.c utils.h
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
	rm $(T)*.o