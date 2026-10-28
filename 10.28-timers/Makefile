CFLAGS = -Wall -Wextra -std=gnu17 -pedantic

all: sporkbomb

debug: CFLAGS += -g
debug: clean all

sporkbomb: spork.o sporkbomb.o
	gcc -o sporkbomb sporkbomb.o spork.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
