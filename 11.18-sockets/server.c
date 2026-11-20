#include <sys/types.h>
#include <sys/socket.h>
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

    /* NOTE: In order for the client to connect to the server, the client must
     *       know the server's port, so the server must additionally bind its
     *       socket to a known port. */

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* NOTE: Accepting a connection creates a new serverside socket connected
     *       to the client, so that the original socket remains bound and
     *       listening for any new connections. */

    client = accept(fd, NULL, NULL);

    while((n = read(client, buf, SIZE)) > 0) {
        buf[n] = '\0';
        printf("Read \"%s\" from a client.\n", buf);
    }

    close(client);
    close(fd);
    freeaddrinfo(addr);
    return EXIT_SUCCESS;
}
