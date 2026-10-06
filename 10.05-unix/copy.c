#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n, src, dest;

    /* NOTE: The system call "open" takes only the bare minimum information to
     *       request that the OS open a file; it returns an integer "file
     *       descriptor", essentially just and index into a behind-the-scenes
     *       array of open files, the "open file table". */
    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    /* NOTE: Although "read" appears to be a function call, it is a system call
     *       and takes longer than an ordinary function call, since it has to
     *       transfer control to/from the OS. By increasing the buffer size, we
     *       decrease the number of system calls, decreasing running time. */
    while ((n = read(src, buf, sizeof(char) * SIZE)) > 0) {
        write(dest, buf, sizeof(char) * n);
    }

    /* NOTE: That file table has finite size; just as "malloc" without "free"
     *       leaks memory on the heap, "open" without "close" leaks file
     *       descriptors, and it is possible to run out of descriptors just as
     *       it is possible to run out of space on the heap. */
    close(src);
    close(dest);

    return 0;
}
