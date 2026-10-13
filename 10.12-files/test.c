#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    /* NOTE: There are myriad reasons why "stat" might fail; for brevity, we
     *       assume in this short lecture example that it succeeds, but we
     *       really should be in the habit of checking the return value and
     *       printing error messages as appropriate. */
    stat(argv[1], &buf);

    /* NOTE: In UNIX, each file is implemented by exactly one "inode" containing
     *       various metadata about the file as well as the locations of its
     *       data blocks -- note files do not actually have names; they are
     *       uniquely identified by their device-inode-number pairs. */
    printf("%s:\n", argv[1]);
    printf("    device: %ld\n", buf.st_dev);
    printf("    inode:  %lu\n", buf.st_ino);
    printf("    size:   %ld\n", buf.st_size);
    printf("    blocks: %ld\n", buf.st_blocks);

    return EXIT_SUCCESS;
}
