list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

# NOTE: As long as we are still testing and debugging, arguably, it's fine to
# 		have warnings; they may just indicate that we haven't finished writing
# 		all of the functions yet.
debug: list.c list.h
	gcc -Wall -Wextra -std=c89 -pedantic -g -c list.c

test: debug
	gcc -Wall -Wextra -std=c89 -pedantic -g listtests.c list.o
	./a.out
