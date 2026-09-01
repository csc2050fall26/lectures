a.out: test.o add.o
	gcc test.o add.o

add.o: add.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c add.c

test.o: test.c add.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c test.c
