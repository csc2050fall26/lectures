CFLAGS = -Wall -Wextra -std=gnu17 -pedantic

all: parent child

debug: CFLAGS += -g
debug: clean all

parent: parent.o
	gcc -o parent parent.o

child: child.o
	gcc -o child child.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
