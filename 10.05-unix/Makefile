# NOTE: As programmers who arguably know what we are doing, we should have the
# 		freedom to ignore warnings and use all of the latest features.
CFLAGS = -Wall -Wextra -std=gnu17 -pedantic

all: copy fcopy

# NOTE: When we build for debugging purposes, we want to include extra debug
# 		information and always recompile from scratch.
debug: CFLAGS += -g
debug: clean all

copy: copy.o
	gcc -o copy copy.o

fcopy: fcopy.o
	gcc -o fcopy fcopy.o

# NOTE: To build an object file, we always want to compile the source file of
# 		the same name (just with a different extension).
%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
