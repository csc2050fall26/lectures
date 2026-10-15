#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int status = EXIT_FAILURE, tmp;
    pid_t child;

    if ((child = fork()) == 0) {
        /* NOTE: This replaces the current process -- the child -- with the
         *       contents of the "./child" program, where by convention the
         *       first argument is always the name of that program. */
        execlp("./child", "child", NULL);

        /* NOTE: A successful call to "exec" effectively never returns -- it
         *       replaces all of this code with the code of "./child", so the
         *       only way to get this far is if it failed. */
        perror("./child");
        exit(EXIT_FAILURE);
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
