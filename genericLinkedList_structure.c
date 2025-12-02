#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50 // macro for character array (string size)

// enum for unique code for data types
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CUSTOM_STRUCT
} DataType;

// user defined data type: structure for adding in one of the linked list node
typedef struct {
    int id;
    char name[MAX];
} CustomStruct;

// main linked list node structure having data, type and addresses
typedef struct List_Node {
    void *data;
    DataType type;
    struct List_Node *next;
    struct List_Node *prev;
} Node;

// function to create a new node for linked list with node type
Node* createNode(void *data, DataType type) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        puts("out of memory.!");
        exit(EXIT_FAILURE);
    }
    newNode->type = type;
    newNode->next = newNode->prev = NULL;
    switch(type) {
        case TYPE_INT: {
            newNode->data = malloc(sizeof(int));
            if(!newNode->data) {
                puts("out of memory.!");
                exit(EXIT_FAILURE);
            }
            *(int*)(newNode->data) = *(int*)data;
            break;
        }
        case TYPE_DOUBLE: {
            newNode->data = malloc(sizeof(double));
            if(!newNode->data) {
                puts("out of memory.!");
                exit(EXIT_FAILURE);
            }
            *(double*)(newNode->data) = *(double*)data;
            break;
        }
        case TYPE_STRING: {
            newNode->data = malloc(MAX * sizeof(char));
            if(!newNode->data) {
                puts("out of memory.!");
                exit(EXIT_FAILURE);
            }
            strcpy((char*)newNode->data, (char*)data);
            break;
        }
        case TYPE_CUSTOM_STRUCT: {
            newNode->data = malloc(sizeof(CustomStruct));
            if(!newNode->data) {
                puts("out of memory.!");
                exit(EXIT_FAILURE);
            }
            memcpy(newNode->data, data, sizeof(CustomStruct));
            break;
        }
        default:
            newNode->data = NULL;
    }
    return newNode;
}

// function to insert a node at head
Node* insertAtHead(Node* head, void *data, DataType type) {
    Node* newNode = createNode(data, type);
    if (!head) {
        return newNode;
    }
    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

// function to insert a node at tail
Node* insertAtTail(Node* head, void *data, DataType type) {
    Node* newNode = createNode(data, type);
    if (!head) {
        return newNode;
    }
    Node *tail = head;
    while(tail->next != NULL)
        tail = tail->next;
    tail->next = newNode;
    newNode->prev = tail;
    return head;
}

// function to free list
void freeList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp->data);
        temp->data = NULL;
        temp->prev = NULL;
        free(temp);
        temp = temp->next;
    }
    temp = NULL;
}

// function to display the data for a single node, depending on its DataType
void displayData(void *data, DataType type) {
    if (data == NULL) {
        printf("[NULL]");
        return;
    }
    switch (type) {
        case TYPE_INT:
            printf("%d", *(int*)data);
            break;
        case TYPE_DOUBLE:
            printf("%.4f", *(double*)data);
            break;
        case TYPE_STRING:
            printf("%s", (char*)data);
            break;
        case TYPE_CUSTOM_STRUCT: {
            CustomStruct *cs = (CustomStruct*)data;
            printf("{id: %d, name: %s}", cs->id, cs->name);
            break;
        }
        default:
            printf("[unknown type]");
    }
}

// function to display all nodes in the list from head to tail
void displayList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        displayData(temp->data, temp->type);
        if (temp->next != NULL)
            printf(" <-> ");
        temp = temp->next;
    }
    printf("\n");
}


int main() {
    Node *head = NULL;

    // Insert int
    int a = 10;
    head = insertAtHead(head, &a, TYPE_INT);

    // Insert double
    double b = 9.81;
    head = insertAtHead(head, &b, TYPE_DOUBLE);

    // Insert string
    char str[] = "Abc";
    head = insertAtHead(head, str, TYPE_STRING);

    // Insert custom struct
    CustomStruct cs = {1, "Linked List" };
    head = insertAtHead(head, &cs, TYPE_CUSTOM_STRUCT);

    printf("\n================\nList contents:\n");
    displayList(head);
    printf("================\n");

    freeList(head);
    return 0;
}