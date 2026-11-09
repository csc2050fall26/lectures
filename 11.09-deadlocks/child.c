#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 81

int main(void) {
    char buf[SIZE];

    fgets(buf, SIZE, stdin);
    buf[strlen(buf) - 1] = '\0'; 
    printf("Hello, %s!\n", buf);

    return EXIT_SUCCESS;
}
