#include <stdio.h>

/* NOTE: Standard library functions like "fread" still have to call "read", but
 *       they add commonly desired functionality: "fread" will "read" more data
 *       than requested and save the excess in memory behind-the-scenes, so
 *       that future calls to "fread" can avoid calling "read" again. */
#define SIZE 128

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    while ((n = fread(buf, sizeof(char), SIZE, src)) > 0) {
        fwrite(buf, sizeof(char), n, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}
