#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, i;
    char buf[] = "Hello, server!";

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the address of the device on which
     *       the server is running and the port with which it is associated. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addr);

    /* NOTE: For simplicity, we'll assume that the first address found by
     *       "getaddrinfo" will always work, rather than iterating over the
     *       linked list of addresses to try. */

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    connect(fd, addr->ai_addr, addr->ai_addrlen);

    /* NOTE: Due to network limitations, it is possible that the entire buffer
     *       cannot be sent at once, in which case it is our responsibility to
     *       try sending the rest later. */

    i = 0;
    while (i < 14) {
        i += write(fd, buf + i, 14 - i);
    }

    /* NOTE: In POSIX, all I/O is file I/O, and sockets are no exception. Just
     *       as with pipes, closing sockets is how we indicate that we will not
     *       be sending or receiving any more data. */

    close(fd);
    freeaddrinfo(addr);
    return EXIT_SUCCESS;
}
