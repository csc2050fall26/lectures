/* NOTE: Like classes, structures define new types by grouping related
 *       variables together for both performance and readability. */
struct Pair {
    int first;
    int second;
};

/* NOTE: The above defines a new type "struct Pair"; the below then gives that
 *       new type the alternative name "Pair". */
typedef struct Pair Pair;
