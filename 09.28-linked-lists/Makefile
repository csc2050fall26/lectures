list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

test: list.o
	gcc -Wall -Wextra -Werror -std=c89 -pedantic listtests.c list.o
	./a.out
