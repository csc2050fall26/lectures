#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, ptoc[2], ctop[2];
    pid_t child;

    /* NOTE: In theory, we could do this with a single pipe if we were very
     *       careful about coordinating exactly which process read and wrote
     *       and when, but in practice it is much easier to just make two
     *       separate pipes. */

    pipe(ptoc);
    pipe(ctop);

    if ((child = fork()) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());

        /* NOTE: In the child, replace stdin/stdout with the appropriate ends
         *       of pipes; note that stderr is left unchanged so that any
         *       error messages will still be visible to the user instead of
         *       being captured by a pipe. */

        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* NOTE: Now that we have access to the pipes via stdin/stdout, all of
         *       the original file descriptors are unnecessary; note that
         *       stdin/stdout are automatically closed once a process
         *       terminates. */

        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./child", "./child", NULL);
        perror("./child");
        exit(EXIT_FAILURE);
    }
    else {
        char buf[SIZE + 1];
        int n;

        printf("Process %d is the parent of %d.\n", getpid(), child);

        /* NOTE: We now have two processes that are both expecting to read and
         *       to write, but they can't both read first, otherwise they will
         *       be "deadlocked" waiting for data that only the other is
         *       capable of writing. */

        close(ptoc[0]);
        close(ctop[1]);
        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);

        while ((n = read(ctop[0], buf, SIZE)) > 0) {
            printf("Process %d read \"%s\" from a pipe.\n", getpid(), buf);
        }

        close(ctop[0]);
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
