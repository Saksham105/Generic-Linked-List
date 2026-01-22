#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "genlist.h"


/*------------DEFINING DEFAULT STRING SIZE------------*/
#define MAX_STRING_SIZE 40


/* Force 1-byte alignment (no padding) */
#pragma pack(push, 1)


/*------------CLIENT DEFINED STRUCTURE------------*/
struct CustomStruct {
    char string_data[MAX_STRING_SIZE];
    int int_data;
};


/* Restore the default alignment settings */
#pragma pack(pop)


/*------------CLIENT DEFINED FUNCTION TO DISPLAY CLIENT DEFINED STRUCTURE------------*/
void show_struct_data(void *data) {
    // type casting the void* to the custom structure pointer
    struct CustomStruct *local_struct_data = (struct CustomStruct*) data;

    printf("[%d],", local_struct_data->int_data);
    printf("[%s]", local_struct_data->string_data);
}


/*------------MAIN FUNCTION------------*/
int main(void) {

    /* To operate with generic behaviour of the linked list, you must pass the structure to the server side. */
    export_structure(sizeof(struct CustomStruct));



    /*----------------------------------------------------------------------------------*/
    list_t *list = NULL;
    status_t status;
    len_t list_length;



    /*----------------------------------------------------------------------------------*/
    int int_data;
    double double_data;
    char char_data;
    // char string_data[MAX_STRING_SIZE];
    struct CustomStruct customStruct_data;


    const char line[] = "----------------------------------------------------------------";



    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("[BEFORE CREATION] Displaying list:");
    status = show_list(list, &show_struct_data);
    assert(status == LIST_EMPTY);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("Creating list");
    list = create_list();



    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("[AFTER CREATION] Displaying list");
    status = show_list(list, &show_struct_data);
    assert(status == SUCCESS);




    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("Inserting all types of data in the end of list");
    puts("\nEnter integer data: ");
    int_data = 100;// fscanf(stdin, "%d", &int_data);
    status = put_back(list, &int_data, INTEGER);
    assert(status == SUCCESS);



    puts("\nEnter character data: ");
    char_data = 'A';// fscanf(stdin, " %c", &char_data);
    status = put_front(list, &char_data, CHARACTER);
    assert(status == SUCCESS);



    puts("\nEnter string data: ");
    // getchar(); // to clear the left '\n' character in input buffer queue
    char string_data[] = "saksham"; // fgets(string_data, MAX_STRING_SIZE, stdin);
    // string_data[strcspn(string_data, "\n")] = '\0';
    status = put_before(list, &int_data, INTEGER, string_data, STRING);
    assert(status == SUCCESS);



    puts("\nEnter double data: ");
    double_data = 9.81;// fscanf(stdin, "%lf", &double_data);
    status = put_after(list, &char_data, CHARACTER, &double_data, DOUBLE);
    assert(status == SUCCESS);



    puts("\nEnter custom struct data: ");
    // puts("Enter int data for struct: ");
    customStruct_data.int_data = 10;// fscanf(stdin, "%d", &customStruct_data.int_data);
    // puts("Enter int data for struct: ");
    strcpy(customStruct_data.string_data, string_data);// fgets(customStruct_data.string_data, MAX_STRING_SIZE, stdin);
    // customStruct_data.string_data[strcspn(customStruct_data.string_data, "\n")] = '\0';
    status = put_back(list, &customStruct_data, STRUCTURE);
    assert(status == SUCCESS);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("[AFTER DATA INSERTION] Displaying list");
    status = show_list(list, &show_struct_data);
    assert(status == SUCCESS);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    list_length = get_list_length(list);
    fprintf(stdout, "List length: %d\n", list_length);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Fetch first node: ");
    node_t *first_node = NULL;
    get_front(list, &first_node);
    show_data(first_node);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Fetch last node: ");
    node_t *last_node = NULL;
    get_back(list, &last_node);
    show_data(last_node);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Fetch node after integer 100: ");
    node_t *middle_node = NULL;
    get_after(list, &int_data, INTEGER, &middle_node);
    show_data(middle_node);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Fetch node before integer 100: ");
    get_before(list, &int_data, INTEGER, &middle_node);
    show_data(middle_node);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Searching for structure data: {%d, %s}\n", customStruct_data.int_data,customStruct_data.string_data);
    status = contains_data(list, &customStruct_data, STRUCTURE);
    assert(status == TRUE);
    if(status == TRUE) {
        puts("Data found.");
    } else {
        puts("Data not found.!");
    }



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Searching for structure data: {%d, %s}\n", customStruct_data.int_data,customStruct_data.string_data);
    status = contains_data(list, &customStruct_data, STRUCTURE);
    assert(status == TRUE);
    if(status == TRUE) {
        puts("Data found.");
    } else {
        puts("Data not found.!");
    }



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Searching for structure data: {%d, %s}\n", customStruct_data.int_data,customStruct_data.string_data);
    status = contains_data(list, &customStruct_data, STRUCTURE);
    assert(status == TRUE);
    if(status == TRUE) {
        puts("Data found.");
    } else {
        puts("Data not found.!");
    }



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Searching for structure data: {%d, %s}\n", customStruct_data.int_data,customStruct_data.string_data);
    status = contains_data(list, &customStruct_data, STRUCTURE);
    assert(status == TRUE);
    if(status == TRUE) {
        puts("Data found.");
    } else {
        puts("Data not found.!");
    }



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Searching for structure data: {%d, %s}\n", customStruct_data.int_data,customStruct_data.string_data);
    status = contains_data(list, &customStruct_data, STRUCTURE);
    assert(status == TRUE);
    if(status == TRUE) {
        puts("Data found.");
    } else {
        puts("Data not found.!");
    }



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Pop first node");
    pop_front(list);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Pop last node");
    pop_back(list);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Pop node after double 9.81");
    pop_after(list, &double_data, DOUBLE);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    fprintf(stdout, "Pop node before integer 100");
    pop_before(list, &int_data, INTEGER);



    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("[AFTER REMOVAL OF DATA] Displaying list");
    status = show_list(list, &show_struct_data);
    assert(status == SUCCESS);
    


    /*----------------------------------------------------------------------------------*/
    puts(line);
    puts("Clearing (destroying) list");
    list = clear_list(list);
    fprintf(stdout, "is list empty? %d\n", isEmpty(list));
    assert(isEmpty(list) == true);



    list = destroy_list(list);
    assert(isEmpty(list) == true);



    return 0;
}