#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, ptoc[2], ctop[2];
    pid_t child;

    /* NOTE: In theory, we could do this with a single pipe, if we were very
     *       careful about coordinating exactly which process read/wrote and
     *       when; in practice, it's much easier to make two pipes: one for
     *       parent-to-child and one for child-to-parent. */

    pipe(ptoc);
    pipe(ctop);

    if ((child = fork()) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());

        /* NOTE: Replace stdin/stdout with the ends of pipes; note that stderr
         *       is left unchanged, so that any error messages will still be
         *       shown to the user at the terminal rather than being captured
         *       in a pipe. */

        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);
        
        /* NOTE: Now that stdin/stdout have been replaced by the relevant ends 
         *       of the pipes, the original file descriptors are entirely
         *       unnecessary in the child; note that stdin/stdout will be
         *       closed automatically on termination. */

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

        /* NOTE: We now have two processes, both of which are planning to read
         *       and to write, but they can't both read first, otherwise they
         *       will be blocked indefinitely waiting for data which only the
         *       other will ever send. */

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
