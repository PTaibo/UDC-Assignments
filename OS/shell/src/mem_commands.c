#include "mem_commands.h"

#include <stdlib.h>
#include <strings.h>

#include "types.h"
#include "error_msgs.h"

struct cmd mem_commands[] = {
    {"malloc", cmd_malloc},
    {"shared", cmd_shared},
    {"mmap", cmd_mmap},
    {"read", cmd_read},
    {"write", cmd_write},
    {"memdump", cmd_memdump},
    {"memfill", cmd_memfill},
    {"mem", cmd_mem},
    {"recurse", cmd_recurse},
    {NULL, NULL}
};

/************************************************************************************************
 * THE CONTESTS OF OUR LIST MUST BE COMMPATIBLE WITH WHAT THE SYSTEM
 * SHOWS WITHH THE PMAP COMMAND (PROCSTAT VM, VMMAP... DEPENDING
 * ON THE PLATFORM
************************************************************************************************/

/*
 * SYSCALLS:
 * - shmget
 * - shmat
 * - malloc
 * - free
 * - mmap
 * - munmap
 * - shmctl
 * - open
 * - read
 * - write
 * - close
 * - ...
 */

int check_mem_commands (int paramN, char* command[])
{
    for (int i = 0; command_list[i].name != NULL; i++){
        if (!strcmp(command[0], command_list[i].name)){
            if(!is_help_param(paramN, command))
                (*command_list[i].funct)(paramN, command+1);
            return 1;
        }
    }
    
    return 0;
}

void cmd_malloc(int paramN, char* command[])
{
    if (!paramN){
        // print list of allocated blocks
    }
    else if (paramN == 1 && atoi(command[0])) {
        // allocate specified amount of space (malloc)
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")){
        // free specified amount of space (free)
    }
    else {
        invalid_param();
    }
}

void cmd_shared(int paramN, char* command[])
{
    if (!paramN) {
        // print list of shared blocks (shmget)
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")){
        // unmap de specified memory block (command[1] = key) (shmdt / ipcs)
        // ayudaP2.c
    }
    else if (paramN == 2 && !strcmp(command[0], "-delkey")){
        // deletes specified key (command[1])
    }
    else if (paramN == 3 && !strcmp(command[0], "-create")){
        // creates shared mem block of size [2] and key [|] (shmget / shmat)
        // flags=IPC_CREAT | IPC_EXCL| permisions
    }
    else {
        invalid_param();
    }
}

void cmd_mmap(int paramN, char* command[])
{
    if (!paramN) {
        // prints list
    }
    else if (paramN == 1) {
        // mapear fichero (mmap)
        // ayudaP2.c
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")) {
        // free specified file (munmap)
    }
    else if (paramN == 2) {
        // mapear fichero con modos especificados
    }
    else {
        invalid_param();
    }
}

void cmd_read(int paramN, char* command[])
{
    if (paramN != 3){
        invalid_param();
        return;
    }

    // Read [2] bytes of file [0] from address [1]
}

void cmd_write(int paramN, char* command[])
{
    if (paramN == 3) {
        // Read write bytes to address/file
    }
    else if (paramN == 4 && !strcmp(command[0], "-o")) {
        // Same but overwriting the file
    }
    else {
        invalid_param();
    }
}

void cmd_memdump(int paramN, char* command[])
{
    if (paramN == 1) {
        // dump address contents to screen
    }
    else if (paramN == 2) {
        // dump specified number of bytes
    }
    else {
        invalid_param();
    }
}

void cmd_memfill(int paramN, char* command[])
{
    if (paramN != 3){
        invalid_param();
        return;
    }
    // Fill n bytes with specified character
}

void cmd_mem(int paramN, char* command[])
{
    if (paramN == 1 && !strcmp(command[0], "-pmap")) {
        // output of pmap command
    }
    else {
        // use bit mask like in stats function
    }
}

void cmd_recurse(int paramN, char* command[])
{
    if (paramN != 1) {
        invalid_param();
        return;
    }

    // repeat the recursive function [0] times
}
