#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List test_list;

void is_empty()
{
    printf("%s\n", (is_empty_list(&test_list)) ? "empty list" : "not empty list");
    fflush(stdin);
}

void can_print()
{
    print_open_files(&test_list);
    fflush(stdin);
}

void new_element (int n)
{
    static int idx = 0;
    char msg[200];

    sprintf(msg, "%d", idx);
    strcat(msg, "_element");

    printf("Message is %s\n", msg);

    printf("Adds element\n");
    add_element(n, msg, &test_list);
    fflush(stdin);
}

void delete_n (int n)
{
    printf("Deletes element %d\n", n);
    delete_element(n, &test_list);
    fflush(stdin);
}

int main(){

    printf("List initialized\n");
    initialize_file_list(&test_list);
    is_empty();
    new_element(3);
    is_empty();
    can_print();
    new_element(2);
    can_print();
    delete_n(3);
    can_print();
    delete_n(3);
    can_print();
}
