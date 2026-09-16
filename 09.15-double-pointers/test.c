#include <stdio.h>

/* NOTE: The value of an array of pointers is the address of its first pointer,
 *       which decays into a double pointer. Note that array and pointer
 *       syntaxes are largely interchangeable */
void f(int **mat) {
    mat[1][0] = 5; /* Interchangeable with "*(*(mat + 1) + 0) = 5". */
}

/* NOTE: Since 2-dimensional arrays are stored in row-major order, the compiler
 *       must know the width in order to do the indexing math, which means this
 *       function only works on (n x 2) arrays. */
void g(int mat[][2]) {
    mat[1][0] = 6; /* Equivalent to "*(mat + 1 * 2 + 0) = 6". */
}

/* NOTE: The compiler sees "mat" here as an ordinary integer pointer, but we
 *       know that that pointer actually contains the address of an (n x m)
 *       array of integers, and we can do the indexing math ourselves. */
void h(int *mat, int m) {
    *(mat + 1 * m + 0) = 7; /* Equivalent to "mat[1][0] = 6". */
}

int main(void) {
    int r0[] = {1, 2}, r1[] = {3, 4};
    int *mat1[2];
    int mat2[][2] = {{1, 2}, {3, 4}};

    mat1[0] = r0;
    mat1[1] = r1;

    f(mat1);

    printf("mat1: %p\n", (void *)mat1);
    printf(" |- %p: %p\n", (void *)&mat1[0], (void *)mat1[0]);
    printf(" |   |- %p: %d\n", (void *)&mat1[0][0], mat1[0][0]);
    printf(" |   +- %p: %d\n", (void *)&mat1[0][1], mat1[0][1]);
    printf(" +- %p: %p\n", (void *)&mat1[1], (void *)mat1[1]);
    printf("     |- %p: %d\n", (void *)&mat1[1][0], mat1[1][0]);
    printf("     +- %p: %d\n", (void *)&mat1[1][1], mat1[1][1]);

    g(mat2);
    h((int *)mat2, 2);

    printf("mat2: %p\n", (void *)mat2);
    printf(" |- %p: %p\n", (void *)&mat2[0], (void *)mat2[0]);
    printf(" |   |- %p: %d\n", (void *)&mat2[0][0], mat2[0][0]);
    printf(" |   +- %p: %d\n", (void *)&mat2[0][1], mat2[0][1]);
    printf(" +- %p: %p\n", (void *)&mat2[1], (void *)mat2[1]);
    printf("     |- %p: %d\n", (void *)&mat2[1][0], mat2[1][0]);
    printf("     +- %p: %d\n", (void *)&mat2[1][1], mat2[1][1]);

    return 0;
}
