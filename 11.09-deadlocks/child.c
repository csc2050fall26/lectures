#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 81

int main(void) {
    char buf[SIZE];
    
    /* NOTE: This process has no idea that any pipes might exist; it expects to
     *       communicate solely using stdin/stdout. By replacing those file
     *       descriptors with the ends of pipes, we can "trick" this process
     *       into using pipes instead. */

    /* NOTE: This program expects to perform all I/O using stdin/stdout; it is
     *       unaware of any pipes we may have created. If we replace stdin and
     *       stdout with the ends of pipes before executing this program, we
     *       can "trick" it into using those pipes instead. */

    fgets(buf, SIZE, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return EXIT_SUCCESS;
}
