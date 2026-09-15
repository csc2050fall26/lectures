#include <stdio.h>

/* NOTE: Since the value of an array is the address of its first element, the
 *       value of an array of pointers must be the address of its first "inner"
 *       pointer, which decays into a double pointer when passed as argument.
 *       The below is equivalent to "*(*(mat + 1) + 0) = 5". */
void f(int **mat) {
    mat[1][0] = 5;
}

/* NOTE: Multidimensional arrays are stored in row-major order; in order to
 *       make the indexing math work out, every inner array must have the same
 *       length. This means that "g" is limited to (n x 2) arrays. */
void g(int mat[][2]) {
    mat[1][0] = 6;
}

void h(int *mat, int m) {
    *(mat + 1 * m + 0) = 7;
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
