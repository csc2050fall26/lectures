# NOTE: Now that we arguably do actually know what we are doing, we should have
# 		the freedom to ignore warnings and use all of the latest features.
CFLAGS = -Wall -Wextra -std=gnu17 -pedantic

all: copy fcopy

# NOTE: When debugging, we want to use the default flags with the addition of
# 		-g, and we want to recompile from scratch every time.
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

# NOTE: Often, when debugging, we want to periodically delete any existing
# 		object files, just to be sure we aren't using older code.
clean:
	rm -f *.o
