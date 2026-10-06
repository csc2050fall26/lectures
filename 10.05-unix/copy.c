#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n, src, dest;

    /* NOTE: The system call "open" passes along only the bare minimimum info.
     *       needed to request that the OS open a file and returns an integer
     *       "file descriptor" -- essentially just an index into an array of
     *       open files, the "open file table". */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* NOTE: Although "read" looks like an ordinary function call, as a system
     *       call, it takes longer, since it has to transfer control to/from
     *       the OS. By increasing the size of the buffer, we decrease the
     *       number of system calls, decreasing the total running time. */
    while ((n = read(src, buf, sizeof(char) * SIZE)) > 0) {
        write(dest, buf, sizeof(char) * n);
    }

    /* NOTE: That file table has finite size; just as "malloc" without "free"
     *       leaks memory on the heap, "open" without "close" leaks file
     *       descriptors, and it is possible to run out of descriptors in the
     *       table just as it is possible to run out of space on the heap. */
    close(src);
    close(dest);

    return 0;
}
