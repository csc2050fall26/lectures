# NOTE: By splitting the compilation up into three steps and depending on the
#       object files rather than the source files, if we change just one of the
#       source files, we can recompile it with the other existing object file
#       rather than recompiling both source files.
a.out: test.o add.o
	gcc test.o add.o

# NOTE: The "-c" flag instructs the compiler to just compile a source file into
#       an object file, containing machine instructions which could then be
#       referenced later as part of some larger program, rather than attempting
#       to form a complete program.
add.o: add.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c add.c

# NOTE: Since the contents of "add.h" will be textually copy-pasted into
# 		"test.c", we need "add.h" in order to compile "test.c", but we don't
# 		need to list "add.h" among the arguments to the compiler; it will
# 		already be a part of "test.c".
test.o: test.c add.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c test.c
