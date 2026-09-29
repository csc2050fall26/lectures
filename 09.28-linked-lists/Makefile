list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

# NOTE: Arguably, as long as we are still in the process of testing and
# 		debugging, it's okay to have warnings; they might just indicate that
# 		we haven't finished yet.
debug: list.c list.h
	gcc -Wall -Wextra -std=c89 -pedantic -g -c list.c

# NOTE: As we are incrementally testing and debugging, we should periodically
# 		run our tests through Valgrind, so as to detect and address any memory
# 		usage issues as soon as possible.
test: debug
	gcc -Wall -Wextra -std=c89 -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
