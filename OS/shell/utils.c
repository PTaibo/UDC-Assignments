#include "utils.h"

int is_number (char* num)
{
    for (int i = 0; num[i] != '\0'; i++){
        if (num[i] > '9' || num[i] < '0'){
            if (num[i] != '-' && num[i] != '+')
                return 0;
        }
    }
    return 1;
}
