#include "mem_commands.h"

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>

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
    if (!strcmp(memb->type, "malloc"))
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

void print_mem_info (mem_block* mem)
{
    printf("%p %10lu %s %s", mem->addr,
                               mem->size,
                               mem->alloc_time,
                               mem->type);
    if (mem->key != -1)
        printf(" (key %d)", mem->key);
    if (mem->fd != -1)
        printf(" %s (fd %d)", mem->file_name,
                               mem->fd);
    printf("\n");
}

void print_memory (char* action, char* type)
{
    printf(GREEN "\n%s memory for process %d\n" RESET_CLR,
            action,
            getpid());
    Pos pos = dynList_first(memList);
    for (; pos != NULL; pos = dynList_next(&pos)){
        mem_block* mem = dynList_getter(pos);
        if (!strcmp(mem->type, type))
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

int allocate_mem (size_t size)
{
    mem_block* info = malloc(sizeof(mem_block));
    if (info == NULL) return 0;
    info->addr = malloc(size);
    printf("%lu bytes allocated at %p\n", size,
                                    info->addr);
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

void free_mem (size_t size)
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
        print_memory("Allocated", "malloc");
    }
    else if (paramN == 1 && atoi(command[0])) {
        if (!allocate_mem(strtoul(command[0], NULL, 10)))
              printf(RED "Error: " RESET_CLR "could not allocate memory\n");
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")){
        free_mem(strtoul(command[1], NULL, 10));
    }
    else {
        invalid_param();
    }
}

int fill_shared_mem_info (key_t key, size_t size, void* address)
{
    mem_block* info = malloc(sizeof(mem_block));
    if (info == NULL) return -1;
    info->addr = address;
    info->size = size;
    info->alloc_time = parse_time();
    info->type = malloc(MAX_COMMAND_SIZE);
    strcpy(info->type, "shared");
    info->key = key;
    info->fd = -1;
    info->file_name = NULL;
    dynList_add(info, &memList);
    return 0;
}

void* get_shared_address (int id, key_t key, size_t size)
{
    void* addrs = shmat(id, NULL, 0);
    if (addrs == (void*) -1){
        int aux = errno;
        if (size)
            shmctl(id, IPC_RMID, NULL);
        errno = aux;
        return NULL;
    }

    if (size)
        printf("Assigned %d bytes at %p\n",
                key, addrs);
    else
        printf("Shared memory with key %d at %p\n",
                key, addrs);
    return addrs;
}

int get_shared_memory (key_t key, size_t size)
{
    int flags = 0777;
    if (size)
        flags = flags | IPC_CREAT | IPC_EXCL;
    if (key == IPC_PRIVATE){
        errno = EINVAL;
        return -1;
    }

    int id;
    if ((id = shmget(key, size, flags)) < 0)
        return -1;

    void* p = get_shared_address(id, key, size);

    struct shmid_ds s;
    shmctl(id, IPC_STAT, &s);
    fill_shared_mem_info(key, s.shm_segsz, p);
    return 0;
}

int free_shared_memory (key_t key)
{
    Pos pos = dynList_first(memList);
    for (; pos != NULL; pos = dynList_next(&pos)){
        mem_block* info = dynList_getter(pos);
        if (info->key == key){
            if (shmdt(info->addr) < 0) return -1;
            dynList_delete(delete_memblock, pos, &memList);
            return 0;
        }
    }
    printf("The process has no blocks mapped with that key");
    return 0;
}

void delete_key (key_t key)
{
    if (key == IPC_PRIVATE)
        printf(RED "Error: " RESET_CLR "not a valid key\n");
    int id = shmget (key, 0, 0666);
    if (id < 0){
        perror ("Impossible to get shared memory");
        return;
    }
    if (shmctl (id, IPC_RMID, NULL) < 0)
        perror("Impossible to eliminate id of shared memory\n");
}

void cmd_shared(int paramN, char* command[])
{
    if (!paramN) {
        print_memory("Shared", "shared");
    }
    else if (paramN == 1) {
        key_t key = (key_t) strtoul(command[0], NULL, 10);
        if (get_shared_memory(key, 0) < 0)
            perror("Couldn't get shared memory");
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")){
        key_t key = (key_t) strtoul(command[1], NULL, 10);
        if (free_shared_memory(key) < 0)
            perror("Couldn't free shared memory");
    }
    else if (paramN == 2 && !strcmp(command[0], "-delkey")){
        key_t key = (key_t) strtoul(command[1], NULL, 10);
        delete_key(key);
    }
    else if (paramN == 3 && !strcmp(command[0], "-create")){
        key_t key = (key_t) strtoul(command[1], NULL, 10);
        size_t size = strtoul(command[2], NULL, 10);
        if (get_shared_memory(key, size) < 0)
            perror("Couldn't create shared memory block");
    }
    else {
        invalid_param();
    }
}

int get_permissions (char* p)
{
    int permissions = 0;
    if (strchr(p, 'r') != NULL)
        permissions |= PROT_READ;
    if (strchr(p, 'w') != NULL)
        permissions |= PROT_WRITE;
    if (strchr(p, 'x') != NULL)
        permissions |= PROT_EXEC;
    return permissions;
}

int fill_mapped_file_info (int fd, char* file, size_t size, void* addrs)
{
    mem_block* info = malloc(sizeof(mem_block));
    if (info == NULL) return -1;
    info->addr = addrs;
    info->size = size;
    info->alloc_time = parse_time();
    info->type = malloc(MAX_COMMAND_SIZE);
    strcpy(info->type, "mapped");
    info->key = -1;
    info->fd = fd;
    info->file_name = malloc(MAX_COMMAND_SIZE);
    strcpy(info->file_name, file);
    dynList_add(info, &memList);
    return 0;
}

int map_file (int permissions, char* file)
{
    int mode = permissions & PROT_WRITE ?  O_RDWR : O_RDONLY;
    struct stat s;
    if (stat(file, &s) < 0){
        return -1;
    }
    int fd = open(file, mode);
    if (fd < 0)
        return -1;
    void* addrs = mmap(NULL, s.st_size, permissions, MAP_PRIVATE, fd, 0);
    if (addrs == MAP_FAILED)
        return -1;
    if (fill_mapped_file_info(fd, file, s.st_size, addrs) < 0)
        return -1;

    printf("Mapped file %s at %p\n", file, addrs);
    return 0;
}

int unmap_file (char* file)
{
    struct stat s;
    if (stat(file, &s) < 0)
        return -1;

    Pos pos = dynList_first(memList);
    for(; pos != NULL; pos = dynList_next(&pos)){
        mem_block* info = dynList_getter(pos);
        if (!strcmp(info->type, "mapped") && !strcmp(info->file_name, file)){
            if (munmap(info->addr, s.st_size) < 0)
                return -1;
            dynList_delete(delete_memblock, pos, &memList);
            return 0;
        }
    }
    printf("No such file mapped in process\n");
    return 0;
}

void cmd_mmap(int paramN, char* command[])
{
    if (!paramN) {
        print_memory("Mapped", "mapped");
    }
    else if (paramN == 1) {
        if (map_file(0, command[0]) < 0)
            perror("Couldn't map file");
    }
    else if (paramN == 2 && !strcmp(command[0], "-free")) {
        if (unmap_file (command[1]) < 0)
            perror("Couldn't unmap file");
    }
    else if (paramN == 2) {
        int permissions = get_permissions(command[1]);
        if (map_file(permissions, command[0]) < 0)
            perror ("Couldn't map file");
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
        close(df);
        errno = aux;
    }
    close (df);
    return n;
}

/*void* stringtopointer (char* direction){
    void* h; 
    sscanf(direction, "%p", &h);
    return h;
}*/

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

    if ((df = open(f, flags, 0777)) == -1 )
        return -1;

    if ((n = write(df, p, amount)) == -1){
        aux = errno;
        close (df);
        errno = aux;
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

void dumpmem (long p, int amount)
{
    long aux = p;
    
    for (int i = 0; i < amount; i++){
        char curretcar = *(char *) p;
        if (curretcar == '\0') {
            continue;
        }
        printf(" %c ",(curretcar == '\n') ? ' ' : curretcar);
        p++;
    }
    printf("\n");

    for(int i = 0; i< amount; i++){
        char curretcar = *(char *) aux;
        if (curretcar == '\0')
            continue;
        printf("%02X ",curretcar);
        aux++;
    }
    printf("\n");
}

void cmd_memdump(int paramN, char* command[])
{
    if (paramN == 1) {
        // dump address contents to screen
        //memdump <add> 
        long p = strtoul (command[0], NULL, 16);
        int amount = 26;

        dumpmem(p, amount);
        
    }
    else if (paramN == 2) {
        // dump specified number of bytes
        //memdump <add> <amount>
        long p;
        int amount = atoi (command[1]);

        p = strtoul(command[0], NULL, 16);

        dumpmem(p, amount);
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
    // repeat the recursive function [0] times
    if (paramN != 1) {
        invalid_param();
        return;
    }

    int n = atoi(command[0]);
    if (n >= 0) makeRecurse(n);
    else makeRecurse(0);
}
