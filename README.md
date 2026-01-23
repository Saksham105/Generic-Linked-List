# Generic-Linked-List
Generic linked list like python


# Command to run project
    >gcc -c genlist.c genlist_main.c
    >gcc genlist.o genlist_main.o -o runApplication
    >runApplication.exe


# Problem statement
    1.  The "Type Explosion" Problem
        In a strictly typed language like C, if you need a list for integers, you write an IntList. If you then need one for floats, you write a FloatList. If your project has 20 different struct types, you would be forced to write 20 nearly identical sets of functions.

        The Problem: Manual duplication of code for every new data type is unsustainable and leads to massive "code bloat."

    2.  Violation of the DRY (Don't Repeat Yourself) Principle
        The logic for inserting a node, deleting a node, or reversing a list is mathematically identical regardless of whether the node holds a char or a complex struct.

        The Problem: If you find a bug in your "Insert" logic, you have to find and fix it in every single type-specific implementation. A generic list allows you to "Write Once, Debug Once."


# Solution
    1.  Designed a Generic Linked list which is able to store different types of data in an unified list.
    2.  Data types suppoted by the list:
            int
            double
            char
            char[] (string)
            custom structure
    3.  Function provided to perform operations on linked list:
            create a list
            create a node
            insertion at front
            insertion at end
            deletion at front
            deletion at front
            display list
            search element in list
            get node count in list
            deallocate list memory
    4.  To display the structure data, client is expected to write its own display logic.
    5.  That logic/function is used by the server to display client structure data.


# Concepts used
    1.  The void* pointer for data storage
    2.  The node pointer for linking of linked list
    3.  The function* pointer for client structure data display
    4.  Enumeration for status (assertion checking)
    5.  Enumeration for datatype indicating which type of data to be stored