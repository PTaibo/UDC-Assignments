#include "mem_commands.h"

#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#include "types.h"
#include "error_msgs.h"
#include "list.h"
#include "help_pages.h"
#include "colors.h"

#define TAM 2048

DynamicList memList;

void init_mem()
{
    dynList_init(&memList);
}

void delete_memblock (void* info)
{
    mem_block* memb = (mem_block*) info;
    free(memb->addr);
    free(memb->alloc_time);
    free(memb->type);
    if (memb->file_name != NULL)
        free(memb->file_name);
}

void rm_mem()
{
    dynList_clear(delete_memblock, &memList);
}

struct cmd mem_commands[] = {
    {"malloc", cmd_malloc},
    /* {"shared", cmd_shared}, */
    /* {"mmap", cmd_mmap}, */
    /* {"read", cmd_read}, */
    /* {"write", cmd_write}, */
    /* {"memdump", cmd_memdump}, */
    /* {"memfill", cmd_memfill}, */
    /* {"mem", cmd_mem}, */
    /* {"recurse", cmd_recurse}, */
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

void print_mem_info (mem_block* mem)
{
    printf("%p %10d %s %s", mem->addr,
                               mem->size,
                               mem->alloc_time,
                               mem->type);
    if (mem->key != -1)
        printf(" (key %d)", mem->key);
    if (mem->fd != -1)
        printf(" %ss (fd %d)", mem->file_name,
                               mem->fd);
    printf("\n");
}

void print_malloc ()
{
    printf(GREEN "\nAllocated blocks for process %d\n" RESET_CLR,
            getpid());
    Pos pos = dynList_first(memList);
    for (; pos != NULL; pos = dynList_next(&pos)){
        mem_block* mem = dynList_getter(pos);
        if (!strcmp(mem->type, "malloc"))
            print_mem_info(mem);
    }
    printf("\n");
}

struct tm* get_time ()
{
    time_t rawtime;
    time (&rawtime);
    return localtime(&rawtime);
}

void time_to_str (struct tm* time, char* str)
{
    char tmp[MAX_COMMAND_SIZE];
    sprintf(tmp, "%d", time->tm_mday);
    strcat(str, tmp); strcat(str, "/");
    sprintf(tmp, "%d", time->tm_mon+1);
    strcat(str, tmp); strcat(str, "/");
    sprintf(tmp, "%d", time->tm_year + 1900);
    strcat(str,tmp); strcat(str, " ");
    sprintf(tmp, "%d", time->tm_hour);
    strcat(str,tmp); strcat(str, ":");
    sprintf(tmp, "%d", time->tm_min);
    strcat(str,tmp);
}

char* parse_time ()
{
    struct tm *t;
    t = get_time();
    char* str = malloc(MAX_COMMAND_SIZE);
    strcpy(str, "");
    time_to_str(t, str);
    return str;
}

int allocate_mem (int size)
{
    mem_block* info = malloc(sizeof(mem_block));
    if (info == NULL) return 0;
    info->addr = malloc(size);
    info->size = size;
    info->alloc_time = parse_time();
    info->type = malloc(MAX_COMMAND_SIZE);
    strcpy(info->type, "malloc");
    info->key = -1;
    info->fd = -1;
    info->file_name = NULL;
    dynList_add(info, &memList);
    return 1;
}

void free_mem (int size)
{
    Pos pos = dynList_first(memList);
    for (; pos != NULL; pos = dynList_next(&pos)){
        mem_block* info = dynList_getter(pos);
        if (strcmp(info->type, "malloc")) continue;
        if (info->size != size) continue;
        dynList_delete(delete_memblock, pos, &memList);
        return;
    }
    printf(RED "Error: " RESET_CLR "no blocks of that size\n");
}

void cmd_malloc(int paramN, char* command[])
{
    if (!paramN){
        print_malloc();
    }
    else if (paramN == 1 && atoi(command[0])) {
        if (!allocate_mem(atoi(command[0])))
            printf(RED "Error: " RESET_CLR "could not allocate memory\n");
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")){
        free_mem(atoi(command[1]));
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

ssize_t readFile (char *f, void *p, size_t amount)
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
    size_t amount = -1;
    ssize_t n;

    p = stringtopointer(command[1]);

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
    ssize_t n;
    void* p;
    size_t amount = -1;
    int over = 0;
    
    if (paramN == 3) {
        // Read write bytes to address/file
        if (strcmp (command[0],"-o"))
            invalid_param();
    
        p = stringtopointer(command[1]);
        if (amount != NULL)
            amount = (size_t) atoll(command[2]);
        
        if((n = writeFile(command[0], p, amount)) == -1)
            perror("Could not write file");

        else 
            printf("Write %lld bytes of %s in %p \n", (long long) n, command[0], p);
    }

    else if (paramN == 4 && !strcmp(command[0], "-o")) {
        // Same but overwriting the file
        if (strcmp (command[0], "-o"))
            over = 1;

        p = stringtopointer(command [2]);
        if(amount != NULL)
            amount = (size_t) atoll (command[3]);

        if((n = writeFile(command[1], p, amount)) == -1)
            perror("Could not write file");
        
        else 
            printf("Write %lld bytes of %s in %p \n", (long long) n, command[0], p);

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
