#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

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
    return '\0';
}
