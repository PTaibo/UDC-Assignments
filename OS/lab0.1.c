#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

off_t BetterGetSizeOfFile (char * name)
{
    struct stat s;

    if (lstat(name, &s) == -1)
        return -1;

    return (s.st_size);
}

off_t GetSizeOfFile (char * name)
{
    struct stat *buff;

    // caloc is malloc but memory is set to all 0 before
    buff = (struct stat*) malloc (sizeof(struct stat*));
    int fileError = lstat (name, buff);

    if (fileError)
        return -1;

    off_t fileSize = buff->st_size;
    free(buff);

    return fileSize;
}


void nada (void)
{
#define MAX 512
    char *p=malloc (MAX);
    int i;

    for (i = 0; i < MAX; i++)
        p[i] = 'Z';
    free(p);
}

int main (int argc, char *argv[])
{
    // Ways of telling printf what type of int is off_t (or any weird ints like that)
    if (argv[1] == NULL){
        printf("usage: %s filename\n", argv[0]);
        return 0;
    }

    off_t fileSize = GetSizeOfFile(argv[1]);

    if (fileSize < 0){
        // Prints error in errno variable (error number set by failed syscall)
        // In man errno you have all the values
        // If errno.h included access to all the macros of the variables (can use)
        // printf("Error number is %d (%s)\n", errno, strerror(errno));
        // ^ to print the error number
        // Difference with printerror: printerror goes to stderror
        //      With printf it goes to standard output
        perror("Cannot access the file");
        return 1;
    }

    printf("size of file %s is %lld\n", argv[1], (long long) fileSize);

    return 0;
}
