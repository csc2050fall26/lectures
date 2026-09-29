list.o: list.c list.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c list.c

# NOTE: As long as we are still testing and debugging, arguably, it's fine to
# 		have warnings; they may just indicate that we haven't finished writing
# 		all of the functions yet.
debug: list.c list.h
	gcc -Wall -Wextra -std=c89 -pedantic -g -c list.c

# NOTE: As we are incrementally testing and debugging, we should periodically
# 		run our tests through Valgrind, so as to detect and address any memory
# 		usage issues as soon as possible.
test: debug
	gcc -Wall -Wextra -std=c89 -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
