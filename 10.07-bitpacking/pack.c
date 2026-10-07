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

    /* NOTE: In UNIX, all I/O appears to be file I/O; to print an error message,
     *       we instead write to "stderr", one of the "files" that pretend to
     *       be the terminal. If a system call fails, it will set the global
     *       "errno", and "perror" can then be used to print a message. */
    if (argc != 3) {
        fprintf(stderr, "usage: ./pack SRC DEST\n");
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

    /* NOTE: If the standard library can do what we need, there is no need to
     *       reinvent that functionality; we need to read 8 characters at a
     *       time and write 1 byte at a time, both of which can already be done
     *       with "fread" and "fwrite". */
    while ((n = fread(buf, sizeof(char), 8, src)) > 0) {
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

    /* NOTE: This function needs to "pack" the characters of "bits" into the
     *       individual bits of "byte", which can be set using bitwise OR; note
     *       that "bits" is indexed left-to-right, but "byte" is indexed right-
     *       to-left; index 0 of "bits" is bit 7 of "byte". */
    for (mask = 1 << 7; mask > 0; mask >>= 1) {
        if (*bits++ == '1') {
            byte |= mask;
        }
    }

    return byte;
}
