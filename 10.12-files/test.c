#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    /* NOTE: For the sake of brevity, in this short lecture example, we'll
     *       assume that "stat" succeeds, but we really should be in the habit
     *       of checking every system call's return value and printing error
     *       messages as appropriate. */
    stat(argv[1], &buf);

    /* NOTE: In UNIX, each file is implemented by exactly one inode, containing
     *       various metadata as well as the locations of the file's blocks on
     *       disk -- note that files do not actually have names; file's names
     *       are mapped to device-inode-number pairs by their directories. */
    printf("%s:\n", argv[1]);
    printf("    device: %ld\n", buf.st_dev);
    printf("    inode:  %lu\n", buf.st_ino);
    printf("    size:   %ld\n", buf.st_size);
    printf("    blocks: %ld\n", buf.st_blocks);

    return EXIT_SUCCESS;
}
