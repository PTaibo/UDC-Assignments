#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include "file_commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <ftw.h>
#include <dirent.h>

#include "types.h"
#include "colors.h"
#include "list.h"
#include "error_msgs.h"
#include "help_pages.h"

file_list opened_files;

void init_file_list()
{
    fileList_initialize(&opened_files);
}

void rm_file_list()
{
    fileList_clear(&opened_files);
}

struct cmd file_commands[] = {
  {"open", cmd_open},
  {"close", cmd_close},
  {"dup", cmd_dup},
  {"listopen", cmd_listopen},
  {"create", cmd_create},
  {"delete", cmd_delete},
  {"deltree", cmd_deltree},
  {NULL, NULL}
};

struct open_flags flags[] = {
    {"cr", O_CREAT},
    {"ap", O_APPEND},
    {"ex", O_EXCL},
    {"ro", O_RDONLY},
    {"rw", O_RDWR},
    {"wo", O_WRONLY},
    {"tr", O_TRUNC},
    {NULL, -1}
};

int check_file_commands (int paramN, char* command[])
{
  for (int i = 0; file_commands[i].name != NULL; i++){
      if (!strcmp(command[0], file_commands[i].name)){
          if (!is_help_param(paramN, command))
              (*file_commands[i].funct)(paramN, command+1);
          return 1;
      }
  }

  return 0;
}

void open_file (char* file, int mode)
{
    int fd = open(file, mode);

    if (fd < 0){
        cannot_open_file();
        return;
    }

    fileList_add (fd, file, &opened_files);
}

void cmd_open (int paramN, char* params[])
{
    if (paramN < 2){
        missing_param();
        return;
    }

    int used_flags = 0;
    for (int j = 1; j < paramN; j++){
        int valid_param = 0;
        for (int i = 0; flags[i].name != NULL; i++){
            if (!strcmp(flags[i].name, params[1])){
                used_flags |= flags[i].flag;
                valid_param = 1;
            }
        }
        if (!valid_param){
            invalid_param();
            return;
        }
    }
    open_file(params[0], used_flags);
}

void cmd_close (int paramN, char* params[])
{
    if (paramN < 1){
        missing_param();
        return;
    }

    int fd = atoi(params[0]);

    // Closing one of the first 3 fds gives segmentation error
    if (paramN > 1 || fd < 3 || fd > MAX_ELEMENTS - 1){
        invalid_param();
        return;
    }
    if (fileList_delete(fd, &opened_files) < 0){
        invalid_param();
        return;
    }
    close(fd);
}

void cmd_dup (int paramN, char* params[])
{
    if (paramN < 1){
        missing_param();
        return;
    }
    
    int fd = atoi(params[0]);

    if (paramN > 1 || fd < 3 || fd > MAX_ELEMENTS - 1){
        invalid_param();
        return;
    }
    if (fileList_dup(fd, &opened_files) < 0){
        perror("Could not duplicate file descriptor");
        return;
    }
    dup(fd);
}

int get_opening_mode (int fd){
    int mode = fcntl(fd, F_GETFL);

    for (int i = 0; flags[i].name != NULL; i++){
        if (mode == flags[i].flag){
            return i;
        }
    }
    mode = mode & O_ACCMODE;
    for (int i = 0; flags[i].name != NULL; i++){
        if (mode == flags[i].flag){
            return i;
        }
    }

    return -1;
}

void cmd_listopen(int paramN, UNUSED char* params[])
{
    if (paramN) {
        invalid_param();
        return;
    }

    printf("   FD  MODE  FILE\n");

    int fd = -1;
    while ((fd = fileList_nextFD(fd, &opened_files)) != -1){
        char file [MAX_COMMAND_SIZE];
        fileList_getter(fd, file, &opened_files);
        int mode = get_opening_mode(fd);

        printf("%5d%5s   %s\n", fd, flags[mode].name, file);
    }
}

void cmd_create (int paramN, char* params[])
{
    // Create new file
    if (paramN == 2 && !strcmp(params[0], "-f")){
        int fd = open(params[1], O_CREAT | O_EXCL, 0644); 
        if (fd < 0){
            perror("Could not create file");
        }
        else {
            close(fd);
        }
    }
    // Create new directory
    else if (paramN == 1){
        if (mkdir(params[0], 0755) < 0){
            perror("Could not create directory");
        }
    }
    else invalid_param();
}

int get_permissions (const char* file)
{
    if (!access(file, W_OK))
        return 1;
    // Write protected files
    if (!access(file, R_OK))
        return 2;
    if (!access(file, X_OK))
        return 2;

    perror("Cannot access file");
    return -1;
}    

void delete_file (const char* file)
{
    int can_delete = get_permissions(file);
    if (can_delete < 0) return;
        
    if (remove(file) < 0){
        printf("Could not remove %s: %s\n",
                            file,
                            strerror(errno));
    }
}

void cmd_delete (int paramN, char* params[])
{
    for (int i = 0; i < paramN; i++){
        delete_file(params[i]);
    }
}

int recursive_delete (const char *fpath,
                       UNUSED const struct stat *sb,
                       UNUSED int typeflag,
                       UNUSED struct FTW *ftwbuf)
{
    delete_file(fpath);
    return 0;
}

void cmd_deltree (int paramN, char* params[])
{
    for (int i = 0; i < paramN; i++){
        if (access(params[i], F_OK)){
            printf("Cannot delete %s: %s\n",
                            params[i],
                            strerror(errno));
        }
        nftw (params[i], recursive_delete, 10, FTW_DEPTH | FTW_PHYS);
    }
}
