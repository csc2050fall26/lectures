#include <stdio.h>

int main(void) {
    short int x = 16384;
    printf("x: %d\n", x);

    /* NOTE: This is valid C syntax, and it compiles and runs without errors or
     *       warnings, but the result is outside the range of a 16-bit short. */
    x *= 2;
    printf("x: %d\n", x);

    /* NOTE: This does not compile; "x" is declared as an integer, and a string
     *       is not an integer.
     * x = "0"; */

    /* NOTE: This may generate a warning, but it is valid syntax; it truncates
     *       0.5 to 0 in order to store it in "x". */
    x = 0.5;
    printf("x: %d\n", x);


    /* NOTE: This is equivalent to (-1 < x) < 1, which is equivalent to 1 < 1,
     *       which evaluates to 0. */
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* NOTE: In ANSI C89, this does not compile; locals have block scope and
     *       must be declared as soon as they come into scope.
     * int y = 1; */

    {
        int y = 1;
        x = 2;

        printf("y (inside): %d\n", y);
        printf("x (inside): %d\n", x);
    }

    /* NOTE: The above introduces a new block, which is a valid place to declare
     *       new locals; once we exit the block, those locals cease to exist.
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}
