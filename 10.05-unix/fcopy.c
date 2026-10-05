#include <stdio.h>

#define SIZE 128

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    /* NOTE: Standard library functions like "fread" still have to make system
     *       calls, but they add additional functionality such as reading more
     *       data than was requested into a buffer behind the scenes, so as to
     *       limit the number of calls to "read". */
    while ((n = fread(buf, sizeof(char), SIZE, src)) > 0) {
        fwrite(buf, sizeof(char), n, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}
