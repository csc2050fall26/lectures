#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int status = EXIT_FAILURE, tmp, i;
    pid_t child;

    /* NOTE: "fork" creates a child process by duplicating the now-parent
     *       process -- the child will receive a copy of the parent's memory,
     *       which means the child will be executing the same instructions;
     *       essentially, "fork" is called once and it returns twice. */

    for (i = 2; i < argc; i++) {
        if ((child = fork()) == 0) {
            printf("Process %d is the child of %d.\n", getpid(), getppid());
            exit(fsearch(argv[i], argv[1]));
        }
        else {
            printf("Process %d is the parent of %d.\n", getpid(), child);
        }
    }

    /* NOTE: It is the parent's responsibility to "wait" for its children; note
     *       that some of the child's resources can't be deallocated until its
     *       parent "wait"s for it. In order to parallelize the children, here
     *       we need to "fork" all the children first before "wait"ing. */

    for (i = 2; i < argc; i++) {
        child = wait(&tmp);

        if (WIFEXITED(tmp)) {
            status = status || WEXITSTATUS(tmp);
            printf("Child %d terminated, status %d.\n", child, WEXITSTATUS(tmp));
        }
        else {
            printf("Child %d terminated abnormally.\n", child);
        }
    }

    return status;
}

/* fsearch: Prints occurrences of a string in a file. */
int fsearch(char *fname, char *str) {
    int status = EXIT_FAILURE;
    char buf[LINELEN];
    FILE *file = fopen(fname, "r");

    while (fgets(buf, LINELEN, file) != NULL) {
        if (strstr(buf, str) != NULL) {
            printf("%s: %s", fname, buf);
            status = EXIT_SUCCESS;
        }
    }

    fclose(file);
    return status;
}
