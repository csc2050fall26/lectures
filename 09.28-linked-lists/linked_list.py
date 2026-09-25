# Implements a linked list.
# CSC 202, code from lecture 
# See also: github.com/csc202winter25/lectures

class List:
    """ An ordered collection of elements """

    def __init__(self):
        # The head of the backing linked list:
        self.head = None
        # The number of elements in this list:
        self.size = 0


class Node:
    """ A single node in a linked list """

    def __init__(self, value, next):
        # The value contained in this node:
        self.value = value
        # The next node in the linked list:
        self.next = next


def get(lst, idx):
    # Start with the current node being the head.
    # For i from 0 to the given idx, do:
    #     Set the current node to the current node's next.
    # Return the current node's value.
    pass


def set(lst, idx, value):
    # Start with the current node being the head.
    # For i from 0 to the given idx, do:
    #     Set the current node to the current node's next.
    # Set the current node's value to the given value.
    pass


def add(lst, idx, value):
    # Create a new node containing the given value.
    #
    # If the given idx is equal to 0, then:
    #     Set the new node's next to the head.
    #     Set the head to the new node.
    # Else, do:
    #     Start with the current node being the head.
    #     For i from 0 to the given idx - 1, do:
    #         Set the current node to the current node's next.
    #     Set the new node's next to the current node's next.
    #     Set the current node's next to the new node.
    #
    # Increment the size.
    pass


def remove(lst, idx):
    # If the given idx is equal to 0, then:
    #     Set the head to the head's next.
    # Else, do:
    #     Start with the current node being the head.
    #     For i from 0 to the given idx - 1, do:
    #         Set the current node to the current node's next.
    #     Set the current node's next to the current node's next's next.
    #
    # Decrement the size.
    pass
