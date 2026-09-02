#include <stdio.h>
#include "add.h"

/* NOTE: This instructs the compiler to replace just about any instance of the
 *       text "PI" with the text "3.14"; by convention, macros are defined in
 *       all-caps, so as to avoid accidentally replacing existing keywords or
 *       identifiers. */
#define PI 3.14

/* NOTE: This instructs the compiler to replace just about any instance of text
 *       of the form "ADD(X, Y)" with "X + Y"; note the addition of parentheses
 *       to avoid any side effects with the surrounding context. This has the
 *       potential to be more efficient and more flexible than a function. */
#define ADD(X, Y) ((X) + (Y))

int main(void) {
    printf("add(PI, PI): %d\n", add(PI, PI));
    printf("ADD(PI, PI): %f\n", ADD(PI, PI));
    printf("ADD(PI, PI) * 2: %f\n", ADD(PI, PI) * 2);

    return 0;
}
