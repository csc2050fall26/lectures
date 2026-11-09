#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 80

int main(void) {
    int status = EXIT_SUCCESS, tmp, fds[2];
    pid_t child;

    pipe(fds);

    if ((child = fork()) == 0) {
        printf("Process %d is the child of %d.\n", getpid(), getppid());

        close(fds[1]);

        execlp("./child", "./child", NULL);
        perror("./child");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Process %d is the parent of %d.\n", getpid(), child);

        close(fds[0]);
        write(fds[1], "parent\n", 7);
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
