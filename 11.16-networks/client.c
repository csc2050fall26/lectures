#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addrs, *addr;

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the server's address and port. This
     *       requests a 32-bit IPv4 address suitable for a TCP connection,
     *       which is the most typical setting. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addrs);

    /* NOTE: Since it is possible that the server has multiple addresses,
     *       "getaddrinfo" produces a pointer to the head of a dynamically
     *       allocated linked list of addresses for us to try, which we are
     *       responsible for deallocating once we are done. */

    addr = addrs;
    while(addr != NULL) {
        uint32_t ipaddr = ntohl(
         ((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

        printf("%d.%d.%d.%d\n",
         (ipaddr & 0xFF000000) >> 24,
         (ipaddr & 0x00FF0000) >> 16,
         (ipaddr & 0x0000FF00) >> 8,
         (ipaddr & 0x000000FF) >> 0);

        addr = addr->ai_next;
    }

    freeaddrinfo(addrs);
    return EXIT_SUCCESS;
}
