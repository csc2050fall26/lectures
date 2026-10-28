#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "spork.h"

int main(void) {
    int status = EXIT_FAILURE, tmp;
    pid_t child;

    if ((child = spork(5)) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());

        while (1) {
            fork();
            perror("fork");
            sleep(1);
        }
    }
    else {
        printf("Process %d is the parent of %d.\n", getpid(), child);
        child = wait(&tmp);

        if (WIFEXITED(tmp)) {
            status = status || WEXITSTATUS(tmp);
            printf("Child %d terminated with %d.\n", child, WEXITSTATUS(tmp));
        }
        else {
            printf("Child %d terminated abnormally.\n", child);
        }
    }

    return status;
}
