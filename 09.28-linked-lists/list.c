#include <stdlib.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate(void) {
    List *lst = (List *)malloc(sizeof(List));

    /* NOTE: Since we don't know how many lists or nodes we will need until
     *       runtime, they will have to be allocated on the heap. That memory
     *       on the heap must be initialized before the List is returned; it
     *       is not necessarily zeroed out. */
    lst->head = NULL;
    lst->size = 0;

    return lst;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    Node *tmp = lst->head, *next;

    /* NOTE: We might call whomever allocates memory the "owner" of that memory;
     *       here, we allocated each Node, and thus we "own" those Nodes and are
     *       responsible for deallocating them. In contrast, we "borrowed" the
     *       values, and we don't even know where they are allocated. */ 
    while (tmp != NULL) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }

    /* NOTE: The standard library doesn't know what we plan to do with allocated
     *       memory; it doesn't know that "lst" points to a List, and that once
     *       a List is deallocated, we have no way of accessing its Nodes, which
     *       thus also ought to be deallocated first. */
    free(lst);
}

/* lstget: Gets an element in a linked list. */
void *lstget(List *lst, int idx) {
    return NULL;
}

/* lstset: Sets an element in a linked list. */
int lstset(List *lst, int idx, void *val) {
    return 0;
}

/* lstadd: Adds an element to a linked list. */
int lstadd(List *lst, int idx, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    if (idx == 0) {
        node->next = lst->head;
        lst->head = node;
    }
    else {
        Node *tmp = lst->head;
        int i;

        for (i = 0; i < idx - 1; i++) {
            tmp = tmp->next;
        }

        node->next = tmp->next;
        tmp->next = node;
    }

    lst->size++;

    /* NOTE: Since "lst" was passed as a pointer, we don't need to return a new
     *       copy of the list; rather, if we cared to check for indices out-of-
     *       bounds, we could return something other than 0 to indicate an
     *       error. */
    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
