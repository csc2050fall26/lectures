#include <stdio.h>

/* NOTE: Since the value of an array is the address of its first element, the
 *       value of an array of pointers must be the address of its first "inner"
 *       pointer, which decays into a double pointer when passed as argument.
 *       The below is equivalent to "*(*(mat + 1) + 0) = 5". */
void f(int **mat) {
    mat[1][0] = 5;
}

/* NOTE: Two-dimensional arrays are stored in "row-major order"; the compiler
 *       must know the length of each "inner" array in order to do the indexing
 *       math. Note function "g" only works on (n x 2) arrays. */
void g(int mat[][2]) {
    mat[1][0] = 6;
}

/* NOTE: Here, the compiler thinks "mat" is just an ordinary integer pointer,
 *       but we happen to know that it will actually be a pointer to the first
 *       element in an (n x m) array, and we can do the indexing ourselves. */
void h(int *mat, int m) {
    *(mat + (1 * m) + 0) = 7;
}

int main(void) {
    int row0[] = {1, 2}, row1[] = {3, 4};
    int *mat1[2];
    int mat2[][2] = {{1, 2}, {3, 4}};

    mat1[0] = row0;
    mat1[1] = row1;

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
