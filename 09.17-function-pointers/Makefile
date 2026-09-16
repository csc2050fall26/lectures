a.out: reduce.o add.o max.o
	gcc reduce.o add.o max.o

reduce.o: reduce.c add.h max.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c reduce.c

add.o: add.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c add.c

max.o: max.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c max.c
