#ifndef GENLIST_H
#define  GENLIST_H

#include <stdbool.h>


/*------------DEFINING STATUS FOR ASSERT CHECKING------------*/
enum Status {
    SUCCESS                 =   1,
    FAILED                  =   0,
    TRUE                    =   1,
    FALSE                   =   0,
    LIST_DATA_NOT_FOUND     =   2,
    LIST_EMPTY              =   3
};


/*------------ENUMERATION DESCRIBING THE DATA TYPE------------*/
enum Data_Type {
    INTEGER                 =   4,
    DOUBLE                  =   5,
    CHARACTER               =   6,
    STRING                  =   7,
    STRUCTURE               =   8,
    NULL_DATA               =   -1
};


/*------------LINKED LIST NODE------------*/
struct List_Node {
    void *data;
    enum Data_Type type;
    struct List_Node *next;
    struct List_Node *prev;
};


/*------------TYPEDEF------------*/
typedef enum Status status_t;
typedef enum Data_Type type_t;
typedef struct List_Node node_t;
typedef node_t list_t;
typedef long unsigned int len_t;
typedef unsigned int size_t;
typedef bool bool_t;


/*------------GLOBAL VARIABLE TO STORE CLIENT STRUCTURE SIZE------------*/
size_t STRUCTURE_SIZE;


/*------------SET THE CLIENT STRUCTURE SIZE AT THE SERVER SIDE------------*/
void export_structure(size_t size);


/*------------CREATE LIST HEAD NODE FUNCTION PROTOTYPE------------*/
list_t* create_list(void);


/*------------INSERT NODE FUNCTION PROTOTYPE------------*/
status_t put_front(list_t*, void*, const type_t);
status_t put_back(list_t*, void*, const type_t);
status_t put_after(list_t*, void*, const type_t, void*, const type_t);
status_t put_before(list_t*, void*, const type_t, void*, const type_t);


/*------------DELETE NODE FUNCTION PROTOTYPE------------*/
status_t pop_front(list_t*);
status_t pop_back(list_t*);
status_t pop_after(list_t*, void*, const type_t);
status_t pop_before(list_t*, void*, const type_t);
status_t remove_data(list_t*, void*, const type_t);


/*------------GET NODE FUNCTION PROTOTYPE------------*/
status_t get_front(const list_t*, node_t**);
status_t get_back(const list_t*, node_t**);
status_t get_after(const list_t*, void*, const type_t, node_t**);
status_t get_before(const list_t*, void*, const type_t, node_t**);


/*------------MISCELLANEOUS FUNCTIONS------------*/
status_t show_list(const list_t*, void (*struct_display)(void*));
void show_data(const node_t*);
status_t contains_data(const list_t*, void*, const type_t);
len_t get_list_length(const list_t*);
bool_t isEmpty(const list_t*);


/*------------DESTROY LIST FUNCTION PROTOTYPE------------*/
list_t* clear_list(list_t*);
list_t* destroy_list(list_t*);


/*------------HELPER FUNCTION PROTOTYPE------------*/
void* xmalloc(size_t);
node_t* create_node(void *, const type_t);
void generic_insert(node_t*, node_t*, node_t*);
void generic_delete(node_t*);
node_t* search_node(const list_t*, void*, const type_t type);


#endif
