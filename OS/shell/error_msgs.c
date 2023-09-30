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

