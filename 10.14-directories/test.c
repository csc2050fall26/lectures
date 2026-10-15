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

    /* NOTE: Every running program has a current working directory; by changing
     *       where we are in the directory tree, we ensure that we can find
     *       all of the files without having to construct their paths in
     *       memory. */
    chdir(argv[1]);

    /* NOTE: Although directories are files, their binary formats are not
     *       standardized; they can be accessed with system calls "open",
     *       "read", etc., but the library functions "opendir", "readdir", etc.
     *       already know how to interpret their binary data correctly. */
    dir = opendir(".");

    /* NOTE: The only information guaranteed to be in an entry is a filename and
     *       its inode number, which can then be used to "stat" the file. Note
     *       also that the entries are in no particular order; if we care about
     *       the order, then we have to sort them ourselves. */
    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &buf);
        printf("%s -> %lu (%ld bytes)\n",
         entry->d_name, entry->d_ino, buf.st_size);
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
