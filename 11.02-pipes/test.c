#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int status = EXIT_SUCCESS, tmp;
    pid_t child;

    if ((child = fork()) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());
    }
    else {
        printf("Process %d is the parent of %d.\n", getpid(), child);

        child = wait(&tmp);

        if (WIFEXITED(tmp)) {
            status = WEXITSTATUS(tmp);
            printf("Child %d terminated with %d.\n", child, status);
        }
        else {
            printf("Child %d terminated abnormally.\n", child);
        }
    }

    return status;
}
