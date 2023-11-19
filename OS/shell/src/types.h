#pragma once

#define MAX_COMMAND_SIZE 200
// Get rid of unused parameter warnings
#define UNUSED __attribute__((unused)) 

struct cmd {
    char *name;
    void (*funct)(int, char**);
};

// Flags for opening files
struct open_flags {
    char* name;
    int flag;
};

struct mem_block {
    void* addrs;
    int size;
    // time of alloc
    // type (malloc, shared, mampped)
    int key;
    int fd;
    char* file_name;
};

