#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int status = EXIT_FAILURE, tmp;
    pid_t child;

    if ((child = fork()) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    else {
        printf("Process %d is the parent of %d.\n", getpid(), child);
        child = wait(&tmp);

        if (WIFEXITED(tmp)) {
            status = WEXITSTATUS(tmp);
            printf("Child %d terminated, status %d.\n", child, WEXITSTATUS(tmp));
        }
        else {
            printf("Child %d terminated abnormally.\n", child);
        }
    }

    return status;
}
