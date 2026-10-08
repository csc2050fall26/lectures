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

    /* NOTE: In UNIX, all I/O appears to be file I/O; if we want to print an
     *       error message, we request that the OS write to "stderr", one of
     *       the files representing the terminal, rather than needed to learn
     *       any terminal-specific system calls. */
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

    /* NOTE: If the standard library can already do what we need, there is no
     *       reason to reimplement that functionality; we need to read 8 chars.
     *       and write 1 byte at a time, both of which can already be handled
     *       with "fread" and "fwrite". */
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

    /* NOTE: This function needs to "pack" the bits indicated by "bits" into
     *       "byte". Note that index 0 of "bits" corresponds to bit 7 of "byte".
     *
     *       Given:
     *        bits = "00100001"
     *        byte = 0b00000000
     *        mask = 0b10000000
     *       ...on the second iteration, we have:
     *        bits = "0100001"
     *        byte = 0b00000000
     *        mask = 0b01000000
     *
     *       ...once the '1' in "mask" is shifted off the end to the right, we
     *       have packed all of the bits.
     *       */

    for (mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*bits++ == '1') {
            byte |= mask;
        }
    }

    return byte;
}
