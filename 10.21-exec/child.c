#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("Process %d is the child of %d.\n", getpid(), getppid());

    return EXIT_SUCCESS;
}
