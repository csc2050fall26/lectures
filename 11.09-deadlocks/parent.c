#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, ptoc[2], ctop[2];
    pid_t child;

    /* NOTE: In theory, we could do all of this with a single pipe if we were
     *       very careful to coordinate who read and who wrote and when; in
     *       practice, it's a lot easier to just make two pipes: one for
     *       parent-to-child data and one for child-to-parent data. */

    pipe(ptoc);
    pipe(ctop);

    if ((child = fork()) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());

        /* NOTE: The child executable has way of knowing about the existence of
         *       these pipes. By replacing stdin/stdout with the appropriate
         *       ends of those pipes, we can "trick" the child into using them
         *       instead of stdin/stdout. */

        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

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

        close(ptoc[0]);
        close(ctop[1]);
        write(ptoc[1], "parent\n", 7);
        close(ptoc[1]);

        /* NOTE: We now have two processes that both intend to read and write,
         *       but they can't both try to read first, otherwise they will be
         *       "deadlocked", forever waiting for the other process to go
         *       first... */

        while ((n = read(ctop[0], buf, SIZE)) > 0) {
            buf[n] = '\0';
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
