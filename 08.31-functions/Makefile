# NOTE: By splitting the compilation up by source file, if one of the source
# 		files changes, we only need to recompile that one object file, which
# 		can then be combined with the other already existing object file.
a.out: test.o add.o
	gcc test.o add.o

# NOTE: By passing the "-c" flag, rather than attempting to form a complete
# 		program (which is impossible without a "main"), we instead just compile
# 		"add.c" into an object file "add.o".
add.o: add.c
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c add.c

# NOTE: Since the contents of "add.h" will be copied into "test.c" before it is
# 		compiled, "test.o" depends on "add.h", but "add.h" does not need to be
# 		passed as a separate argument to the compiler.
test.o: test.c add.h
	gcc -Wall -Wextra -Werror -std=c89 -pedantic -c test.c
