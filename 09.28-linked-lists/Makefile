list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

# NOTE: Arguably, as long as we are still in the process of testing and
# 		debugging, it's okay to have warnings; they might just indicate that
# 		we haven't finished yet.
debug: list.c list.h
	gcc -Wall -Wextra -std=c89 -pedantic -g -c list.c

test: debug
	gcc -Wall -Wextra -std=c89 -pedantic -g listtests.c list.o
	./a.out
