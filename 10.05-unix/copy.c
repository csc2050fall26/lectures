#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n, src, dest;

    /* NOTE: The system call "open" requests that the OS open a file; it passes
     *       along only the bare minimum information required by the OS, no
     *       extras that can be done without the OS, and returns a "file
     *       descriptor", essentially an index into the "open file table". */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* NOTE: Although they look like function calls, system calls take longer,
     *       since they have to transfer control to/from the OS. By increasing
     *       the size of the buffer, we decrease the number of system calls,
     *       thereby decreasing the running time. */
    while ((n = read(src, buf, sizeof(char) * SIZE)) > 0) {
        write(dest, buf, sizeof(char) * n);
    }

    close(src);
    close(dest);

    return 0;
}
