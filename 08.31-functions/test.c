/* NOTE: This instructs the compiler to textually copy-paste the contents of
 *       "stdio.h" and "add.h" into to this file. Angle brackets indicate a
 *       header in the standard library, whereas quotes indicate a header that
 *       we ourselves created. */
#include <stdio.h>
#include "add.h"

int main(void) {
    printf("add(1, 2): %d\n", add(1, 2));
    printf("add(-3, 4): %d\n", add(-3, 4));
    printf("add(0, -5): %d\n", add(0, -5));

    return 0;
}
