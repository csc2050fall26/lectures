#include <stdio.h>

int main(void) {
    short int x = 16384;
    printf("x: %d\n", x);

    /* NOTE: This is perfectly valid C syntax, and it compiles and runs without
     *       errors or warnings, but it is outside the range of a short int. */
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: This will not compile; "x" has been declared as an integer, and a
     *       a string is not an integer
     * x = "0"; */
    x = 0;

    /* NOTE: Since booleans are integers, where 0 is falsey, this is equivalent
     *       to (-1 < x) < 1, which is equivalent to 1 < 1, which is false. */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: In ANSI C89, this does not compile; local variables may only be
     *       declared as soon as they come into scope... 
     * int y = 1; */

    /* NOTE: ...if we create a block, we create a new scope, within which we
     *       may declare new local variables. */
    {
        int y = 1;

        printf("y (inside): %d\n", y);
        printf("x (inside): %d\n", x);
    }

    /* NOTE: Variables are local to their nearest enclosing scope, so once we
     *       exit the above block, "y" ceases to exist.
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}
