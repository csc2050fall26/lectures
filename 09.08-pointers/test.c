#include <stdio.h>

void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    /* NOTE: Rather than passing copies of "z" and "w", this passes pointers to
     *       them; rather than telling "swap" *what* the values of "z" and "w"
     *       are, this tells it *where* in memory they can be found... */
    swap(&z, &w);

    /* NOTE: NULL is equivalent to 0 and guaranteed to be an invalid address
     *       for data; the following is undefined and will likely cause a
     *       segmentation fault attempting to dereference null pointers.
     * swap(NULL, NULL); */

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

void swap(int *x, int *y) {
    /* NOTE: ...in C, arguments are always pass-by-value, but the value of a
     *       pointer is a reference. Using pointers, we can effectively opt-in
     *       to pass-by-reference behavior whenever we want. */
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}
