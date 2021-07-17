FLAGS = -Wall -Wextra -Werror -std=c99 -g

#declaracion de destinos
main: main.o interprete.o contacto.o utils.o tablahash.o
	gcc $(FLAGS) -o $@.out $@.o interprete.o contacto.o utils.o tablahash.o -lm

main.o:	main.c  interprete.h contacto.h tablahash.h
	gcc $(FLAGS) -c	main.c

interprete.o: interprete.c interprete.h contacto.h tablahash.h
	gcc $(FLAGS) -c interprete.c

contacto.o: contacto.c contacto.h utils.h
	gcc $(FLAGS) -c contacto.c

utilis.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c

tablahash.o: tablahash.c tablahash.h
	gcc $(FLAGS) -c tablahash.c -lm

clean:
	rm	*.o
	rm  *.out