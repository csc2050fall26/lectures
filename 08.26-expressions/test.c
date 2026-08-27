#include <stdio.h>

int main(void) {
    short int x = 16384;
    printf("x: %d\n", x);

    /* NOTE: This is perfectly valid C syntax, and compiles and runs without
     *       errors or warnings, but it is outside the range of a short. */
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: Variables are statically typed and generally mutable; this will not
     *       compile, as a string is not an integer.
     * x = "0"; */
    x = 0.5;
    printf("x: %d\n", x);

    /* NOTE: This is equivalent to (-1 < x) < 1, which is equivalent to 1 < 1,
     *       which evaluates to 0. */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: In ANSI C89, this does not compile; variables must be declared as
     *       soon as they come into scope.
     * int y = 1; */

    {
        int y = 1;
        x = 2;

        printf("y (inside): %d\n", y);
        printf("x (inside): %d\n", x);
    }

    /* NOTE: The above creates a new block, the beginning of which is a valid
     *       place to declare new locals, but they are inaccessible outside.
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}
