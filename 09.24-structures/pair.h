/* NOTE: A structure is essentially a class with no methods: it groups related
 *       variables together both for readability and for performance
 * Represents a pair of integers */
struct Pair {
    int first;
    int second;
};

/* NOTE: The definition above defines the new type "struct Pair"; the
 *       definition below then defines "Pair" as a new name for the existing
 *       type "struct Pair". */
typedef struct Pair Pair;
