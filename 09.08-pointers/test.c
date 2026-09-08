#include <stdio.h>

void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    /* NOTE: A null pointer is guaranteed to be an invalid address for data;
     *       dereferencing a null pointer will cause a "segmentation fault", as
     *       the program attempts to access memory outside its "segment".
     * swap(NULL, NULL); */

    /* NOTE: By passing the addresses of "z" and "w" rather than the variables
     *       themselves, we essentially tell "swap" *where* in memory "z" and
     *       "w" can be found rather than *what* their values are... */
    swap(&z, &w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

void swap(int *x, int *y) {
    /* NOTE: ...in C, arguments are always pass-by-value, but the value of a
     *       pointer is a reference! Using pointers, we can effectively opt-in
     *       to pass-by-reference behavior whenever we want. */
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}
