#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List test_list;

void can_print(int n)
{
    print_n_elements(n, &test_list);
    printf("\n");
}

void new_element ()
{
    static int idx = 0;
    char msg[200];

    sprintf(msg, "%d", idx++);
    strcat(msg, "_element");

    append_element(msg, &test_list);
    fflush(stdin);
}

void clear ()
{
    printf("Clears list\n");
    clear_list(&test_list);
    fflush(stdin);
}

int main()
{
    printf("List initialized\n");
    initialize_hist(&test_list);

    can_print(3);
    can_print(-1);

    new_element();
    can_print(-1);
    new_element();
    can_print(-1);
    new_element();
    can_print(1);

    clear();
    can_print(-1);

    new_element();
    new_element();
    can_print(3);
    new_element(0);
    can_print(-1);

    for (int i = 0; i < MAX_ELEMENTS+2; i++){
        new_element();
    }
    can_print(-1);
}
