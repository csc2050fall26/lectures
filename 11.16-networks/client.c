#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addrs, *addr;

    /* NOTE: This program, the client, will actively attempt to connect to the
     *       server, which requires knowing the server's address and port. Note
     *       this requests an address suitable for a TCP/IPv4 connection, which
     *       is typically the most common setting.*/

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(argv[1], argv[2], &hints, &addrs);

    /* NOTE: Since it is generally possible for a device to have multiple
     *       addresses, "getaddrinfo" produces a dynamically allocated linked
     *       list of addresses for us to try; it is our responsibility to
     *       deallocate that list once we are done. */

    addr = addrs;
    while (addr != NULL) {
        uint32_t ipaddr = ntohl(
         ((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

        printf("%d.%d.%d.%d\n",
         (ipaddr & 0xFF000000) >> 24,
         (ipaddr & 0x00FF0000) >> 16,
         (ipaddr & 0x0000FF00) >> 8,
         (ipaddr & 0x000000FF) >> 0);

        addr = addr->ai_next;
    }

    /* NOTE: None of this opens a connection to the server or even guarantees
     *       that a connection, if attempted, would be successful. It simply
     *       obtains the information necessary to try to open a connection. */

    freeaddrinfo(addrs);
    return EXIT_SUCCESS;
}
