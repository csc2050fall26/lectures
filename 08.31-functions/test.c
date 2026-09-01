/* NOTE: These direct the compiler to copy-paste the text within "stdio.h" and
 *       "add.h" into this file. Note angle brackets are used for headers in the
 *       standard library; quotes are used for headers of our own. */
#include <stdio.h>
#include "add.h"

int main(void) {
    printf("add(1, 2): %d\n", add(1, 2));
    printf("add(-3, 4): %d\n", add(-3, 4));
    printf("add(0, -5): %d\n", add(0, -5));

    return 0;
}
