#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    stat(argv[1], &buf);
    printf("%s -> %lu\n", argv[1], buf.st_ino);

    return EXIT_SUCCESS;
}
