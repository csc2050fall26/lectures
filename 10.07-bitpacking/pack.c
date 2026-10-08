#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int n;
    FILE *src, *dest;

    /* NOTE: In UNIX, all I/O appears to be file I/O; if we wish to display an
     *       error message, we request that the OS write to stderr, the "file"
     *       that represents the portion of the terminal responsible for
     *       displaying error messages. */
    if (argc != 3) {
        fprintf(stderr, "usage: ./pack SOURCE DESTINATION\n");
        return EXIT_FAILURE;
    }

    if ((src = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        return EXIT_FAILURE;
    }

    if ((dest = fopen(argv[2], "w")) == NULL) {
        perror(argv[2]);
        fclose(src);
        return EXIT_FAILURE;
    }

    /* NOTE: If the standard library can accomplish what we need, there is no
     *       reason to reinvent that functionality; we need to read 8 chars.
     *       and write 1 byte at a time, both of which can already be done with
     *       "fread" and "fwrite". */
    while ((n = fread(buf, sizeof(char),  8, src)) > 0) {
        while (n < 8) {
            buf[n++] = '0';
        }

        byte = stob(buf);
        fwrite(&byte, sizeof(char), 1, dest);
    }

    fclose(src);
    fclose(dest);

    return EXIT_SUCCESS;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0, mask;

    /* NOTE: This function needs to pack the bits of "bits" into "byte"; note
     *       index 0 of "bits" corresponds to bit 7 of "byte". Given:
     *           bits = "00100001"
     *           byte = 0b00000000
     *           mask = 0b10000000
     *
     *       ... after the first iteration, we have:
     *           bits = "0100001"
     *           byte = 0b00000000
     *           mask = 0b01000000
     *
     *       ...once the '1' in "mask" gets shifted off the right side, "mask"
     *       will be 0, which is how we know we have packed all of the bits. */

    for(mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*bits++ == '1') {
            byte |= mask;
        }
    }

    return byte;
}
