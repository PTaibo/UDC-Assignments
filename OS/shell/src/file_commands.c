#include "file_commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
          if (paramN > 0 && !strcmp(command[1], "-?"))
              cmd_help(paramN, command + 1);
          else
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
        perror("Coudn't open file");
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
    if (paramN > 2){
        invalid_param();
        return;
    }

    for (int i = 0; flags[i].name != NULL; i++){
        if (!strcmp(flags[i].name, params[1])){
            open_file(params[0], flags[i].flag);
            return;
        }
    }

    invalid_param();
}

void cmd_close (int paramN, char* params[])
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
        printf("Could not duplicate file descriptor");
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
    if (paramN == 2 && !strcmp(params[0], "-f")){
        if (open(params[1], O_CREAT, 0644) < 0){
            perror("Couldn't create file");
        }
        return;
    }
    else if (paramN == 1){
        if (mkdir(params[0], 0755) < 0){
            perror("Couldn't create directory");
        }
        return;
    }
    invalid_param();
}

