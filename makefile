FLAGS = -Wall -Wextra -Werror -std=c99 -g

#declaracion de destinos
main: main.o interprete.o contacto.o utils.o tablahash.o archivos.o
	gcc $(FLAGS) -o $@.out $@.o interprete.o contacto.o utils.o archivos.o tablahash.o -lm

main.o:	main.c  interprete.h contacto.h tipos_de_datos/tablahash.h
	gcc $(FLAGS) -c	main.c

archivos.o: archivos.c archivos.h tipos_de_datos/tablahash.h
	gcc $(FLAGS) -c archivos.c

interprete.o: interprete.c interprete.h contacto.h tipos_de_datos/tablahash.h
	gcc $(FLAGS) -c interprete.c

contacto.o: contacto.c contacto.h utils.h
	gcc $(FLAGS) -c contacto.c

utilis.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c

tablahash.o: tipos_de_datos/tablahash.c tipos_de_datos/tablahash.h
	gcc $(FLAGS) -c tipos_de_datos/tablahash.c -lm

clean:
	rm *.o
	rm *.out