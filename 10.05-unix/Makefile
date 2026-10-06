# NOTE: Now that we actually know what we are doing, we should have the freedom
# 		to ignore warnings and to make use of all the latest features.
CFLAGS = -Wall -Wextra -std=gnu17 -pedantic

all: copy fcopy

# NOTE: When debugging, we want to include any extra debug information and
#       always recompile from scratch.
debug: CFLAGS += -g
debug: clean all

copy: copy.o
	gcc -o copy copy.o

fcopy: fcopy.o
	gcc -o fcopy fcopy.o

# NOTE: This essentially says that compiling any object file requires the C
#       source file of the same name.
%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
