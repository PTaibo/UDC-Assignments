#include "error_msgs.h"

#include <stdio.h>

#include "colors.h"

void invalid_param()
{
    printf(RED "Error: " RESET_CLR "Invalid parameter\n");
}

void missing_param()
{
    printf(RED "Error: " RESET_CLR "Missing parameters\n");
}

void mem_fail()
{
    printf(RED "Error: " RESET_CLR "Could not allocate memory\n");
}

void cannot_open_dir()
{
    perror(RED "Error: " RESET_CLR "Could not open directory");
}

void cannot_open_file()
{
    perror(RED "Error: " RESET_CLR "Coudl not open file");
}

