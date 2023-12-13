#pragma once

#define MAX_COMMAND_SIZE 200
// Get rid of unused parameter warnings
#define UNUSED __attribute__((unused)) 

#include <time.h>
#include <sys/shm.h>

struct cmd {
    char *name;
    void (*funct)(int, char**);
};

// Flags for opening files
struct open_flags {
    char* name;
    int flag;
};

// Signal values
struct map {
    char *name;
    int value;
};

typedef struct {
    void* addr;
    size_t size;
    char* alloc_time;
    char* type; // malloc, shared, mapped
    key_t key;
    int fd;
    char* file_name;
} mem_block;

typedef struct {
    pid_t pid;
    char *name;
    char *launch_time;
    int status;
    // ? command line
} process;

