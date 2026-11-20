#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, client, n;
    char buf[SIZE + 1];

    /* NOTE: This program, the server, will already be running, passively
     *       waiting for clients to attempt to connect to it. Thus, the server
     *       need not know the clients' addresses ahead of time. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, argv[1], &hints, &addr);

    /* NOTE: Since the client needs to know the server's address and port in
     *       order to establish a connection, the server's socket must be bound
     *       to a specific, predetermined port number. */

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* NOTE: If the server needed to know information about the client, such as
     *       its IP address, it could pass pointers to structures to "accept",
     *       which would be populated with that information. */

    client = accept(fd, NULL, NULL);

    /* NOTE: When a connection is accepted, a new socket is created to
     *       communicate with the client, leaving the original socket bound and
     *       listening for any new connections. */

    while ((n = read(client, buf, SIZE)) > 0) {
        buf[n] = '\0';
        printf("Read \"%s\" from the client socket.\n", buf);
    }

    close(client);
    close(fd);
    freeaddrinfo(addr);
    return EXIT_SUCCESS;
}
