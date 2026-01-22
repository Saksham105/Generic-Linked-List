#include "genlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



/*------------INITIALIZE THE STRUCTURE SIZE VARIABLE (global)------------*/
void export_structure(size_t size) {
    if(size <= 0) {
        STRUCTURE_SIZE = 8; // bydefault set 8 bytes
    }
    STRUCTURE_SIZE = size;
}



/*------------ALLOCATE ONE MEMORY BLOCK DYNAMICALLY------------*/
void* xmalloc(size_t size)
{
    /*Allocating a memory block of given size.*/
    void *block = malloc(size);

    /*Checking whether the memory is actually allocated or not.
    If not, printing error messege and exit the program.*/
    if(!block) {
        puts("[Error]: xmalloc()\\ fatal error\\ out of memory.!");
        return (NULL); // return NULL: if no memory available.
    }

    return (block);
}



/*------------CREATE ONE NODE------------*/
node_t* create_node(void * data, const type_t type)
{
    /*Creating new memory for the node using xmalloc().*/
    node_t *newNode = (node_t*) xmalloc(sizeof(node_t));

    /*Setting data into the data section, datatype in the type section and NULL in the address section.*/
    newNode->data = data;
    newNode->type = type;
    newNode->next = newNode->prev = newNode; // circular connection to a node.

    return newNode;
}



/*------------CREATE LIST------------*/
list_t* create_list(void)
{
    /*Create one node (head node) with null data, which will hold the entire list in its next pointer.
    This node will never be changed, whatever the operation done to the list. (push, pop, etc)*/
    return create_node(NULL, NULL_DATA);
}



/*------------CHECK IS LIST EMPTY ?------------*/
bool_t isEmpty(const list_t *list) {
    if(!list) 
        return (true);

    return (list->next == list && list->prev == list);
}



/*------------INSERT ONE NODE AT THE FRONT OF THE LIST------------*/
status_t put_front(list_t *list, void * data, const type_t type)
{
    node_t *newNode = create_node(data, type);

    /* if list is not created, create one. */
    if(!list)
        list = create_list();
    
    /* insert the node at first position. */
    generic_insert(list, newNode, list->next);

    return (SUCCESS);
}



/*------------INSERT ONE NODE AT THE END OF THE LIST------------*/
status_t put_back(list_t *list, void * data, const type_t type)
{
    node_t *newNode = create_node(data, type);

    if(!list)
        list = create_list();

    generic_insert(list->prev, newNode, list);

    return (SUCCESS);
}



/*------------INSERT ONE NODE AFTER AN EXISTING NODE------------*/
status_t put_after(list_t *list,
    void * existing_data, const type_t existing_type,
    void * new_data, const type_t new_type)
{
    /* if list is empty, can't insert. */
    if(isEmpty(list))
        return (LIST_EMPTY);

    /* search existing data node in the list. */
    node_t *target_node = search_node(list, existing_data, existing_type);

    /* if data not present in the list, notify that back. */
    if(!target_node)
        return (LIST_DATA_NOT_FOUND);
    
    /* create new node to insert after existing node. */
    node_t *newNode = create_node(new_data, new_type);

    /* simply insert new node at its position. */
    generic_insert(target_node, newNode, target_node->next);

    return (SUCCESS);
}



/*------------INSERT ONE NODE BEFORE AN EXISTING NODE------------*/
status_t put_before(list_t *list,
    void * existing_date, const type_t existing_type,
    void * new_data, const type_t new_type)
{
    if(isEmpty(list))
        return (LIST_EMPTY);
    
    node_t *target_node = search_node(list, existing_date, existing_type);
    if(!target_node)
        return (LIST_DATA_NOT_FOUND);

    node_t *newNode = create_node(new_data, new_type);

    generic_insert(target_node->prev, newNode, target_node);

    return (SUCCESS);
}



/*------------REMOVE ONE NODE FROM THE FRONT OF THE LIST------------*/
status_t pop_front(list_t *list) {
    /* if list is not created: can't delete. */
    if(isEmpty(list))
        return (LIST_EMPTY);

    /* simply delete the 1st node.*/
    generic_delete(list->next);

    return (SUCCESS);
}



/*------------REMOVE ONE NODE FROM THE END OF THE LIST------------*/
status_t pop_back(list_t *list) {
    if(isEmpty(list))
        return (LIST_EMPTY);

    generic_delete(list->prev);

    return (SUCCESS);
}



/*------------REMOVE ONE NODE AFTER AN EXISTING NODE------------*/
status_t pop_after(list_t *list, void *existing_data, const type_t existing_type) {
    if(isEmpty(list))
        return (LIST_EMPTY);

    node_t *target_node = search_node(list, existing_data, existing_type);
    if(!target_node)
        return (LIST_DATA_NOT_FOUND);

    if(target_node->next == list)
        return (FAILED);

    generic_delete(target_node->next);

    return (SUCCESS);
}



/*------------REMOVE ONE NODE BEFORE AN EXISTING NODE------------*/
status_t pop_before(list_t *list, void *existing_data, const type_t existing_type) {
    if(isEmpty(list))
        return (LIST_EMPTY);

    node_t *target_node = search_node(list, existing_data, existing_type);
    if(!target_node)
        return (LIST_DATA_NOT_FOUND);

    if(target_node->prev == list)
        return (FAILED);

    generic_delete(target_node->prev);

    return (SUCCESS);
}



/*------------REMOVE ONE DATA NODE FROM THE LIST------------*/
status_t remove_data(list_t *list, void * delete_data, const type_t delete_type) {
    /* if list is not created: can't delete. */
    if(isEmpty(list))
        return (LIST_EMPTY);

    /* search the node containing data similar to the data want to delete. */
    node_t *target_node = search_node(list, delete_data, delete_type);
    if(!target_node)
        return (LIST_DATA_NOT_FOUND);

    /* simply delete the searched node from the list. */
    generic_delete(target_node);
}



/*------------FETCH THE FIRST NODE FROM THE LIST------------*/
status_t get_front(const list_t *list, node_t **front_node) {
    /* if list is empty: can't get 1st node. */
    if(isEmpty(list))
        return (LIST_EMPTY);

    /* store 1st node data in the front_node. */
    *front_node = create_node(list->next->data, list->next->type);

    return (SUCCESS);
}



/*------------FETCH THE LAST NODE FROM THE LIST------------*/
status_t get_back(const list_t *list, node_t **last_node) {
    if(isEmpty(list))
        return (LIST_EMPTY);

    *last_node = create_node(list->prev->data, list->prev->type);

    return (SUCCESS);
}



/*------------FETCH THE NODE AFTER EXISTING NODE------------*/
status_t get_after(const list_t *list,
    void *existing_data, const type_t existing_type,
    node_t **target_node)
{
    if(isEmpty(list))
        return (LIST_EMPTY);

    node_t *existing_target_node = search_node(list, existing_data, existing_type);
    if(!existing_target_node)
        return (LIST_DATA_NOT_FOUND);

    if(existing_target_node->next == list)
        return (FAILED);

    *target_node = create_node(existing_target_node->next->data, existing_target_node->next->type);

    return (SUCCESS);
}



/*------------FETCH THE NODE BEFORE EXISTING NODE------------*/
status_t get_before(const list_t *list,
    void *existing_data, const type_t existing_type,
    node_t **target_node)
{
    if(isEmpty(list))
        return (LIST_EMPTY);

    node_t *existing_target_node = search_node(list, existing_data, existing_type);
    if(!existing_target_node)
        return (LIST_DATA_NOT_FOUND);

    if(existing_target_node->prev == list)
        return (FAILED);

    *target_node = create_node(existing_target_node->prev->data, existing_target_node->prev->type);

    return (SUCCESS);
}



/*------------SHOW LIST NODES ONE BY ONE------------*/
status_t show_list(const list_t *list, void (*struct_display)(void*)) {
    if(isEmpty(list))
        return (LIST_EMPTY);

    node_t *current = list->next;
    fprintf(stdout, "[START] <-> ");
    while(current != list) {
        if(current->type == STRUCTURE) {
            fprintf(stdout, "{");
            struct_display(current->data);
            fprintf(stdout, "} <->");
        } else {
            show_data(current);
        }

        current = current->next;
    }
    fprintf(stdout, "[END]\n");

    return (SUCCESS);
}



/*------------SHOW ONE NODE DATA------------*/
void show_data(const node_t *data_node) {
    if(!data_node)
        return;
    
    switch(data_node->type) {
        case INTEGER:
            fprintf(stdout, "[%d] <-> ", *(int*)data_node->data);
            break;
        case DOUBLE:
            fprintf(stdout, "[%lf] <-> ", *(double*)data_node->data);
            break;
        case CHARACTER:
            fprintf(stdout, "[%c] <-> ", *(char*)data_node->data);
            break;
        case STRING:
            fprintf(stdout, "[%s] <-> ", (char*)data_node->data);
            break;
    }
}



/*------------SEARCH DATA IN THE LIST------------*/
status_t contains_data(const list_t *list, void * data, const type_t type) {
    if(isEmpty(list)) {
        return (LIST_EMPTY);
    }
    node_t *target_node = search_node(list, data, type);
    if(!target_node)
        return (FALSE);
    return (TRUE);
}



/*------------GET LIST NODES COUNT (length)------------*/
len_t get_list_length(const list_t *    list) {
    if(isEmpty(list))
        return 0;
    
    node_t *current = list->next;
    len_t length = 0;

    while(current != list) {
        length++;
        current = current->next;
    }

    return length;
}



/*------------DEALLOCATE THE DYNAMIC MEMORY OF ALL NODES------------*/
list_t* clear_list(list_t *list) {
    if(isEmpty(list))
        return (list);

    node_t *current = list->next;
    node_t *next_node;
    while(current != list) {
        next_node = current->next;
        list->next = next_node;
        next_node->prev = list;
        free(current);

        current = next_node;
    }

    // reseting the list linking...
    list->next = list->prev = list;
    return (list);
}



/*------------DEALLOCATE THE DYNAMIC MEMORY OF ENTIRE LIST------------*/
list_t* destroy_list(list_t *list) {
    if(!list)
        return (list);

    if(!isEmpty(list)) {
        list = clear_list(list);
    }

    free(list);

    return (NULL);
}



/*------------INSERTS NODE BETWEEN START AND END NODES------------*/
void generic_insert(node_t *start_node, node_t *mid_node, node_t *end_node) {
    start_node->next = mid_node;
    mid_node->prev = start_node;
    mid_node->next = end_node;
    end_node->prev = mid_node;
}



/*------------DELETES NODE------------*/
void generic_delete(node_t *mid_node) {
    mid_node->prev->next = mid_node->next;
    mid_node->next->prev = mid_node->prev;

    free(mid_node);
    mid_node = NULL;
}



/*------------DEALLOCATE THE DYNAMIC MEMORY OF ALL NODES------------*/
node_t* search_node(const list_t *list, void * data, const type_t type) {
    if(isEmpty(list))
        return (NULL);
    
    node_t *current = list->next;
    while(current != list) {
        if(current->type == type) {
            switch(type) {
                case INTEGER:
                    if(memcmp(current->data, data, sizeof(int) == 0)) {
                        return (current);
                    }
                    // if(*(int*)(current->data) == *(int*)data){
                    //     return (current);
                    // }
                    break;
                case DOUBLE:
                    if(memcmp(current->data, data, sizeof(double) == 0)) {
                        return (current);
                    }
                    // if(*(double*)(current->data) == *(double*)data){
                    //     return (current);
                    // }
                    break;
                case CHARACTER:
                    if(memcmp(current->data, data, sizeof(char) == 0)) {
                        return (current);
                    }
                    // if(*(char*)(current->data) == *(char*)data){
                    //     return (current);
                    // }
                    break;
                case STRING:
                    char *str = (char*)current->data;
                    size_t string_size = strlen(str);
                    if(memcmp(current->data, str, string_size) == 0) {
                        return (current);
                    }
                    // if(strcmp((*(char**)(current->data)), (*(char**)data)) == 0){
                    //     return (current);
                    // }
                    break;
                case STRUCTURE:
                    // HOW TO COMPARE ...?
                    if(memcmp(current->data, data, STRUCTURE_SIZE) == 0) {
                        return (current);
                    }
                    break;
                default:
                    return (NULL);
            }
        }
        current = current->next;
    }

    return (NULL);
}