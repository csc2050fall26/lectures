CFLAGS = -Wall -Wextra -std=gnu17 -pedantic

all: pack

debug: CFLAGS += -g
debug: clean all

pack: pack.o
	gcc -o pack pack.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
