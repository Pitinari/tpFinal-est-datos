FLAGS = -Wall -Wextra -Werror -std=c99 -g

#declaracion de destinos
main: main.o interprete.o
	gcc $(FLAGS) -o $@.out $@.o interprete.o -lm

main.o:	main.c  interprete.h
	gcc $(FLAGS)	-c	main.c -lm

interprete.o: interprete.c interprete.h
	gcc $(FLAGS) -c interprete.c -lm

clean:
	rm	*.o
	rm  *.out