#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;
    struct dirent *entry;
    DIR *dir;

    /* NOTE: Every running program has a current working directory relative to
     *       which file paths are evaluated. By changing into the given
     *       directory, we can access the files within without computing their
     *       full paths on the fly. */
    chdir(argv[1]);

    /* NOTE: Although directories are files, and can be accessed with "open",
     *       "read", etc., their binary formats on disk are not standardized;
     *       the library functions "opendir", "readdir", etc. exist to interpret
     *       the contents of a directory correctly for us. */
    dir = opendir(".");

    /* NOTE: The only information guaranteed to be in an entry is a filename and
     *       the inode to which it is mapped. Note that the entries are not in
     *       any particular order; if we care about the order, then we have to
     *       read them into an array and sort them ourselves. */
    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &buf);
        printf("%s -> %lu (%ld bytes)\n",
         entry->d_name, entry->d_ino, buf.st_size);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
