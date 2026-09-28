list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

# NOTE: Arguably, warnings are okay as long as we're still testing and debugging;
#       a warning may simply indicate that we haven't finished implementing a
#       function yet.
debug: list.c list.h
	gcc -Wall -Wextra -std=c89 -pedantic -c list.c

test: debug
	gcc -Wall -Wextra -Werror -std=c89 -pedantic listtests.c list.o
	./a.out
