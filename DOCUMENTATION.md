# Generic Linked List Library - Documentation

---

## Table of Contents

1. [Overview](#overview)
2. [Rules for Usage](#rules-for-usage)
3. [Server-Side (Library Core)](#server-side-library-core)
    - [Data Structures](#data-structures)
    - [Global Variables](#global-variables)
    - [Function List & Descriptions](#server-functions)
4. [Client-Side (Usage Example)](#client-side-usage-example)
    - [Client-defined Structures and Functions](#client-defined-structures-and-functions)
    - [Sample Usage Flow](#sample-usage-flow)
    - [Function Calls (Client Flow)](#function-calls-client-flow)
5. [Appendix: Error Codes](#appendix-error-codes)
6. [End](#end)

---

## Overview

This project implements a **Generic Doubly Linked List in C**, inspired by the versatile `list` in Python. It enables storage of elements with arbitrary data types (integer, double, char, string, and custom structures) using void pointers and runtime type tagging. The codebase is divided into a "server side" (the core, reusable, generic linked list code) and a "client side" (demonstration/driver code that uses the linked list for specific types).

### Why Use a Generic Linked List?

The need for a generic linked list arises from the following reasons:

1. **Type Agnosticism:** Unlike standard C linked lists, this implementation can store and manage elements of any data type (similar to Python lists), greatly increasing flexibility and reducing code duplication for different element types.
2. **Reusability:** The same data structure and set of functions can be reused across projects or modules regardless of stored type, reducing maintenance effort and fostering code modularity.
3. **Complex Data Management:** With the ability to handle custom structures, the generic list enables the creation of advanced data containers for real-world applications, all with strong runtime type checking for safer operations.

---

## Rules for Usage

- **MANDATORY:** Before using the generic linked list for custom structures, the client MUST call `export_structure(sizeof(YourStructure));` immediately after program startup and before any insertion or structure operations.
    - This sets the internal structure size required for correct memory allocation and comparison.
    - Skipping this step will lead to incorrect handling of client-defined structures.

---

## Server-Side (Library Core)

### Data Structures

- **Status Codes**: `enum Status` for operation results (e.g., SUCCESS, FAILED, etc.)
- **Data Types**: `enum Data_Type` used to tag node’s data at runtime (`INTEGER`, `DOUBLE`, `CHARACTER`, `STRING`, `STRUCTURE`)
- **Node Structure**: 

```c
struct List_Node {
    void *data;
    enum Data_Type type;
    struct List_Node *next;
    struct List_Node *prev;
};
```

- **Type Definitions**: Aliases for common types (`status_t`, `type_t`, `node_t`, `list_t`, etc.)

---

### Global Variables

- `size_t STRUCTURE_SIZE;`
    - Used for handling custom structure memory operations (settable at runtime).

---

### Function List & Descriptions

#### 1. **Creation & Deletion**
- `void export_structure(const size_t size)`
    - Sets the size of client-side structures for memory operations.
    - Must be called from the client before working with structure data.

- `list_t* create_list(void)`
    - Allocates and returns a dummy "head" node for the new list.

- `list_t* clear_list(list_t*)`
    - Deletes all nodes from a list except the dummy node; resets list to empty.

- `list_t* destroy_list(list_t*)`
    - Frees all memory associated with a list, including the dummy node.

#### 2. **Node Insertion**
- `status_t put_front(list_t*, void*, const type_t)`
    - Inserts data at the **front** of the list.

- `status_t put_back(list_t*, void*, const type_t)`
    - Inserts data at the **end** of the list.

- `status_t put_after(list_t*, void* existing_data, const type_t existing_type, void* new_data, const type_t new_type)`
    - Inserts new data node **after** a node containing specific data.

- `status_t put_before(list_t*, void* existing_data, const type_t existing_type, void* new_data, const type_t new_type)`
    - Inserts new data node **before** a node containing specific data.

#### 3. **Node Removal**
- `status_t pop_front(list_t*)`
    - Removes the first actual data node (not dummy node).

- `status_t pop_back(list_t*)`
    - Removes the last actual data node.

- `status_t pop_after(list_t*, const void*, const type_t)`
    - Removes the node *after* the specified node.

- `status_t pop_before(list_t*, const void*, const type_t)`
    - Removes the node *before* the specified node.

- `status_t remove_data(list_t*, const void*, const type_t)`
    - Removes the node containing specific data.

#### 4. **Data Access & Information**
- `status_t get_front(const list_t*, node_t**)`
    - Fetches and copies the first data node (if any) into a pointer.

- `status_t get_back(const list_t*, node_t**)`
    - Fetches and copies the last data node.

- `status_t get_after(const list_t*, const void*, const type_t, node_t**)`
    - Gets the node after a specified node.

- `status_t get_before(const list_t*, const void*, const type_t, node_t**)`
    - Gets the node before a specified node.

- `len_t get_list_length(const list_t*)`
    - Returns the total number of data nodes.

- `bool_t isEmpty(const list_t*)`
    - Returns whether the list is empty.

- `status_t contains_data(const list_t*, const void*, const type_t)`
    - Checks if a node with the specified data exists.

#### 5. **Display & Helpers**
- `status_t show_list(const list_t*, void (*struct_display)(void*))`
    - Iterates and prints all nodes, calling a client-supplied function for STRUCTURE-type data.

- `status_t show_data(const node_t*, void (*struct_display)(void*))`
    - Prints a single node’s data, calling client function for STRUCTURE.

- `void* xmalloc(const size_t)`
    - Allocation helper with error checking.

- `node_t* create_node(void *, const type_t)`
    - Helper for node memory allocation and initialization.

- `void generic_insert(node_t*, node_t*, node_t*)`
    - Low-level function to link a node between two other nodes.

- `void generic_delete(node_t*)`
    - Unlinks and frees a given node.

- `node_t* search_node(const list_t*, const void*, const type_t)`
    - Searches for a node matching the given data/type.

---

## Client-Side (Usage Example)

### Client-defined Structures and Functions

- **Custom Structure Example:**
    - `struct CustomStruct { char string_data[MAX_STRING_SIZE]; int int_data; };`

- **Custom Display Function:**
    - `void show_struct_data(void *data);`
        - Prints out the members of the custom structure (used by `show_list`, `show_data`).

---

### Sample Usage Flow

1. **Set up structure size:**
    - `export_structure(sizeof(struct CustomStruct));`
    - Ensures correct handling of STRUCTURE-type nodes.

2. **Create list:**
    - `list = create_list();`

3. **Add elements of different types:**
    - `put_back(list, &int_data, INTEGER);`
    - `put_front(list, &char_data, CHARACTER);`
    - `put_before(list, &int_data, INTEGER, string_data, STRING);`
    - `put_after(list, &char_data, CHARACTER, &double_data, DOUBLE);`
    - `put_back(list, &customStruct_data, STRUCTURE);`

4. **View list:**
    - `show_list(list, &show_struct_data);`

5. **Fetch, search, and check data:**
    - `get_front(list, &first_node);`
    - `get_back(list, &last_node);`
    - `get_after(list, &some_data, TYPE, &node);`
    - `contains_data(list, &customStruct_data, STRUCTURE);`
    - And so forth.

6. **Remove nodes:**
    - `pop_front(list);`
    - `pop_back(list);`
    - `pop_after(list, &some_data, TYPE);`
    - `pop_before(list, &some_data, TYPE);`

7. **Final cleanup:**
    - `clear_list(list);`
    - `destroy_list(list);`

---

### Function Calls (Client Flow)

1. **Initialization**
    - Custom structure declaration.
    - Display function definition.

2. **Set structure size**
    - *REQUIRED when using STRUCTURE*: `export_structure()`

3. **Create list and interact using API**

4. **For all display operations (`show_list`, `show_data`) with STRUCTURE nodes**:
    - The client must provide a suitable display function, cast to `void (*)(void*)`.

---

## Appendix: Error Codes and Status

1. `SUCCESS`: Operation succeeded.
2. `FAILED`: Operation failed.
3. `LIST_DATA_NOT_FOUND`: Data not found in list.
4. `LIST_EMPTY`: List is empty or not created.
5. `INVALID_TYPE`: Data type is invalid.
6. `INVALID_DATA`: Data is invalid or NULL.
7. `MEMORY_ERROR`: Could not allocate memory (typically fatal, treat as out-of-memory).

## End: 

1. Thus the