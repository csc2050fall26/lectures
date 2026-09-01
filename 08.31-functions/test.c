/* NOTE: This instructs the compiler to copy-paste the textual contents of
 *       other files into this file before actually compiling the code. Angle
 *       brackets indicate header files in the standard library, whereas quotes
 *       indicate header files that we ourselves created. */
#include <stdio.h>
#include "add.h"

int main(void) {
    printf("add(1, 2): %d\n", add(1, 2));
    printf("add(-3, 4): %d\n", add(-3, 4));
    printf("add(0, -5): %d\n", add(0, -5));

    return 0;
}
