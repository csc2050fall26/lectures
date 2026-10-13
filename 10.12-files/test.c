#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    /* NOTE: For the sake of brevity, we'll assume in this short lecture
     *       example that "stat" always succeeds, but we really should be in
     *       the habit of checking the return value and printing an error
     *       message as appropriate. */
    stat(argv[1], &buf);

    /* NOTE: In UNIX, every file is implemented by exactly one inode, which
     *       contains various metadata and identifies the locations of blocks
     *       containing its data on disk -- files do not have names; they are
     *       uniquely identified by their device-inode-number pairs. */
    printf("%s:\n", argv[1]);
    printf("    device: %ld\n", buf.st_dev);
    printf("    inode:  %lu\n", buf.st_ino);
    printf("    size:   %ld\n", buf.st_size);
    printf("    blocks: %ld\n", buf.st_blocks);

    return EXIT_SUCCESS;
}
