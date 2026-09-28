list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

# NOTE: Arguably, warnings are okay as long as we're still testing and debugging;
#       a warning may simply indicate that we haven't finished implementing a
#       function yet.
debug: list.c list.h
	gcc -Wall -Wextra -std=c89 -pedantic -g -c list.c

# NOTE: As we incrementally implement and test our functions, we should make
# 		sure to run our tests through Valgrind so as to address any potential
# 		memory leaks as soon as possible.
test: debug
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
