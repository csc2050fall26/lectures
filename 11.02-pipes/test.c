#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, fds[2];
    pid_t child;

    /* NOTE: Create a pipe before creating a child process, so that the child
     *       will inherit access to the pipe by virtue of being a duplicate of
     *       the parent. */
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

        /* NOTE: With pipes, closing unused descriptors is no longer just a
         *       matter of best practice or cleanliness; it's how we indicate
         *       that we are done with those ends of the pipes. */
        close(fds[0]);

        /* NOTE: A pipe is essentially a queue accessible within multiple
         *       processes; anything written to the write end can then be read
         *       by any process with access to the read end. */
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
