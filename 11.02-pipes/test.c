#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, fds[2];
    pid_t child;

    /* NOTE: Since pipes are not actually stored on disk, this pipe must be
     *       created before forking the child, so that the child can inherit
     *       access by virtue of being a duplicate of the parent. */
    pipe(fds);

    if ((child = fork()) == 0) {
        char buf[SIZE + 1];
        int n;

        printf("Process %d is the child of %d.\n", getpid(), getppid());

        close(fds[1]);

        while ((n = read(fds[0], buf, SIZE)) > 0) {
            buf[n] = '\0';
            printf("Process %d read \"%s\" from the pipe.\n", getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        printf("Process %d is the parent of %d.\n", getpid(), child);

        /* NOTE: With pipes, closing unused file descriptors is not just a
         *       matter of cleanliness; its how we notify other processes that
         *       we won't be using the pipe in the future. */
        close(fds[0]);

        /* NOTE: A pipe is essentially a queue; any data that is enqueued by
         *       writing to the "write end" can be dequeued in that same order
         *       by reading from the "read end". */
        write(fds[1], "Hello, child!", 13);

        /* NOTE: Once we are done writing to a pipe, we ought to close its
         *       write end so as to indicate that we will not be writing any
         *       more data in the future. */
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
