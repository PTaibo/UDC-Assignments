#include "mem_commands.h"

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "types.h"
#include "error_msgs.h"
#include "help_pages.h"

#define TAM 2048

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
    for (int i = 0; mem_commands[i].name != NULL; i++){
        if (!strcmp(command[0], mem_commands[i].name)){
            if(!is_help_param(paramN, command))
                (*mem_commands[i].funct)(paramN, command+1);
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
        size_t n = atol (command [0]);
        printf("%p",malloc(n));
        
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

ssize_t readFile (char *f, void *p, ssize_t amount)
{
    struct stat stats;
    ssize_t n;
    int df, aux;

    if (stat (f, &stats) == -1 || (df = open(f, O_RDONLY)) == -1)
        return -1;

    if (amount == -1)
        amount= stats.st_size;

    if ((n = read(df, p, amount)) == -1){
        aux = errno;
    }
    close (df);
    return n;
}

void* stringtopointer (char* direction){
    void* h; 
    sscanf(direction, "%p", &h);
    return h;
}

void cmd_read(int paramN, char* command[])
{
    if (paramN != 3){
        invalid_param();
        return;
    }

    void *p;
    ssize_t amount = -1;
    ssize_t n;

    p = (void *) strtoul(command[1] ,NULL ,16);
    //p = stringtopointer(command[1]);

    if (command[2] != NULL)
    amount = (size_t) atoll(command[2]);

    if ((n = readFile(command[0], p, amount)) == -1)
        perror ("Could not read file");
    else printf("Read %lld bytes of %s in %p \n", (long long) n, command[0], p);

    // Read [2] bytes of file [0] from address [1]
}

ssize_t writeFile (char *f, void *p, size_t amount, int overwrite)
{
    ssize_t n;
    int df, aux, flags = O_CREAT | O_EXCL | O_WRONLY;

    if (overwrite)
        flags = O_CREAT | O_WRONLY | O_TRUNC;

    if ((df = open (f, flags, 0777)) == -1 )
        return -1;

    if ((n = write(df, p, amount)) == -1){
        aux = errno;
        close (df);
        return -1;
    }

    close (df);
    return n;
}

void cmd_write(int paramN, char* command[])
{
    if (paramN == 3) {
        ssize_t n;
        void* p;
        size_t amount = -1;
        int over = 0;
        // Read write bytes to address/file
        if (strcmp (command[0],"-o"))
            invalid_param();
    
        p = (void *) strtoul(command[1] ,NULL ,16);
        //p = stringtopointer(command[1]);
        if (command[2] != NULL)
            amount = (size_t) atoll(command[2]);
        
        if((n = writeFile(command[0], p, amount, over)) == -1)
            perror("Could not write file");

        else 
            printf("Write %lld bytes of %s in %p \n", (long long) n, command[0], p);
    }

    else if (paramN == 4 && !strcmp(command[0], "-o")) {
        // Same but overwriting the file
        ssize_t n;
        void* p;
        size_t amount = -1;
        int over = 0;
        if (strcmp (command[0], "-o"))
            over = 1;

        p = (void *) strtoul(command[2] ,NULL ,16);
        //p = stringtopointer(command [2]);
        if(command[3] != NULL)
            amount = (size_t) atoll (command[3]);

        if((n = writeFile(command[1], p, amount, over)) == -1)
            perror("Could not write file");
        
        else 
            printf("Write %lld bytes of %s in %p \n", (long long) n, command[0], p);

    }
    else {
        invalid_param();
    }
}

void cmd_memdump(int paramN, UNUSED char* command[])
{
    if (paramN == 1) {
        // dump address contents to screen
        //memdump <add> 
        
    }
    else if (paramN == 2) {
        // dump specified number of bytes
        //memdump <add> <amount>
    }
    else {
        invalid_param();
    }
}

void fillmem (void *p, size_t amount, unsigned char byte)
{
    unsigned char* arr = (unsigned char *) p;
    size_t i;

    for (i = 0; i < amount; i++){
        arr[i] = byte;
    }
    printf("Assigned %lld bytes in %p\n", (long long) amount, p);
    return;
}

void cmd_memfill(int paramN, char* command[])
{
    if (paramN != 3){
        invalid_param();
        return;
    }
    // Fill n bytes with specified character
    size_t amount = atoll(command[1]);
    void* p = (void *) strtoul(command[0] ,NULL ,16);
    //void* p = stringtopointer(command[0]);
        
    unsigned char byte = command[2][1];

    fillmem(p, amount, byte);
    return;
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

void makeRecurse (int n)
{
  char automatico[TAM];
  static char estatico[TAM];

  printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

  if (n>0)
    makeRecurse(n-1);
}


void cmd_recurse(int paramN, char* command[])
{
    if (paramN != 1) {
        invalid_param();
        return;
    }

    int n = atoi(command[0]);
    if (n >= 0) makeRecurse(n);
    else makeRecurse(0);
    // repeat the recursive function [0] times
}
