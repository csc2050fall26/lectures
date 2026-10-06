#include <stdio.h>

/* NOTE: Standard library functions like "fread" still have to call "read", but
 *       they add additional common functionality. For example, "fread" will
 *       read more data than we asked for and save the excess in a secret
 *       buffer, so as to avoid calling "read" again in the future. */
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
