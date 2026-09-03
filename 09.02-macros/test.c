#include <stdio.h>
#include "add.h"

/* NOTE: This replaces just about any instance of the text "PI" with "3.14"; by
 *       convention, all-caps make it obvious that this is a macro. */
#define PI 3.14

/* NOTE: This replaces just about any instance of text of the form "ADD(X, Y)"
 *       with the corresponding text of the form "X + Y". */
#define ADD(X, Y) ((X) + (Y))

int main(void) {
    /* NOTE: Macros are generally more efficient than true functions; calling a
     *       function takes longer than just evaluating its body. */
    printf("add(1, 2): %d\n", add(1, 2));
    printf("ADD(1, 2): %d\n", ADD(1, 2));

    /* NOTE: Macros can also be more flexible than functions, since their
     *       arguments do not have to be declared with types. */
    printf("add(PI, PI): %f\n", (double)add(PI, PI));
    printf("ADD(PI, PI): %f\n", (double)ADD(PI, PI));

    /* NOTE: Since a macro is a naive search-and-replace, we should always add
     *       parens to avoid inadvertent interactions with surrounding code.
     * printf("ADD(1-, 2): %d\n", ADD(1-, 2)); */
    printf("ADD(1, 2) * 3: %d\n", ADD(1, 2) * 3);

    return 0;
}
