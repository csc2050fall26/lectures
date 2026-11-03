#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, fds[2];
    pid_t child;

    /* NOTE: Create a pipe; this must be done before creating the child
     *       process, which will inherit access by virtue of being a duplicate
     *       of the parent, since pipes are not exposed via the file system. */
    pipe(fds);

    if ((child = fork()) == 0) {
        char buf[SIZE + 1];
        int n;

        printf("Process %d is the child of %d.\n", getpid(), getppid());

        close(fds[1]);

        /* NOTE: A pipe is essentially a queue: anything the parent has
         *       enqueued by writing to the pipe can then be dequeued by the
         *       child by reading from the pipe. */
        while ((n = read(fds[0], buf, SIZE)) > 0) {
            buf[n] = '\0';
            printf("Process %d read \"%s\" from the pipe.\n", getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        printf("Process %d is the parent of %d.\n", getpid(), child);

        /* NOTE: With pipes, closing unused file descriptors is not just a
         *       matter of best practice to avoid leaking resources; its how we
         *       indicate that we are done with a pipe. */
        close(fds[0]);

        /* NOTE: In UNIX, all I/O appears to be file I/O, and pipes are no
         *       exception; once we have access to the relevant descriptors, we
         *       can use our existing read/write system calls. */
        write(fds[1], "Hello, child!", 13);

        /* NOTE: By closing the write end of a pipe, we indicate to the OS (and
         *       thus to any other process that may be reading from the pipe)
         *       that we will not be sending more data in the future. */
        close(fds[1]);

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
