/* NOTE: Like classes, structures group related variables together both for
 *       readability and also for performance. */
struct Pair {
    int first;
    int second;
};

/* NOTE: The above defines a new type "struct Pair"; the below then gives that
 *       new type the alternative name "Pair". */
typedef struct Pair Pair;
