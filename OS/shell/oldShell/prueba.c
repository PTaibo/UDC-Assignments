#include "list.h"

List hist;
create_list (hist);

printf("%s\n", is_empty_list(list) ? "Emtpy list" : "Not empty list");

add_element(NULL, "ls", hist);
add_element(NULL, "cd", hist);

get_element(0, hist);

