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
     *       "file descriptor", essentially just an index into a behind-the-
     *       scenes "open file table". */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* NOTE: Although system calls appear as ordinary function calls, they take
     *       longer, since they have to securely transfer control to/from the
     *       OS. By increasing the buffer size, we decrease the number of system
     *       calls, thereby decreasing the total running time. */
    while ((n = read(src, buf, sizeof(char) * SIZE)) > 0) {
        write(dest, buf, sizeof(char) * n);
    }

    /* NOTE: The open file table has some fixed size, so if we leak file
     *       descriptors by only ever opening files and never closing them,
     *       we will eventually run out. */
    close(src);
    close(dest);

    return 0;
}
