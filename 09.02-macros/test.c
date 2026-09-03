#include <stdio.h>
#include "add.h"

/* NOTE: This replaces just about any instance of the text "PI" with the text
 *       "3.14"; note the absence of a trailing semicolon. */
#define PI 3.14

/* NOTE: This replaces just about any instance of text of the form "ADD(X, Y)"
 *       with the corresponding text of the form "X + Y". */
#define ADD(X, Y) ((X) + (Y))

int main(void) {
    /* NOTE: Macros have the potential to be more efficient than true functions;
     *       calling a function takes longer than just evaluating its body. */
    printf("add(1, 2): %d\n", add(1, 2));
    printf("ADD(1, 2): %d\n", ADD(1, 2));

    /* NOTE: Macros can also be more flexible than functions; in this case,
     *       since the arguments have no type, it also works on floats. */
    printf("add(PI, PI): %f\n", (double)add(PI, PI));
    printf("ADD(PI, PI): %f\n", (double)ADD(PI, PI));

    /* NOTE: Since a macro is a naive textual search-and-replace, we must be
     *       careful to parenthesize to avoid unintenional side effects. */
    printf("ADD(1-, 2): %d\n", ADD(1-, 2));
    printf("ADD(1, 2) * 3: %d\n", ADD(1, 2) * 3);

    return 0;
}
