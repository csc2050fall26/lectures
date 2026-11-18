#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the address of the device on which
     *       the server is running and the port with which it is associated. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addr);

    /* NOTE: For simplicity, we'll assume that the first address found by
     *       "getaddrinfo" will always work, rather than iterating over the
     *       linked list of addresses to try. */

    freeaddrinfo(addr);
    return EXIT_SUCCESS;
}
