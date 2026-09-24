/* NOTE: Like classes, structures define new types by grouping related
 *       variables together for both performance and readability.
 * Represents a pair of integers */
struct Pair {
    int first;
    int second;
};

/* NOTE: The above defines the new type "struct Pair"; the below then defines
 *       "Pair" as a new name for the existing type "struct Pair", so that we
 *       need not use the "struct" keyword everywhere. */
typedef struct Pair Pair;
