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
#include <pwd.h>
#include <grp.h>
#include <ftw.h>

#include "types.h"
#include "colors.h"
#include "list.h"
#include "error_msgs.h"
#include "help_pages.h"

#define P_LONG 1
#define P_ACC 2
#define P_LINK 4
#define P_RECA 8
#define P_RECB 16
#define P_HID 32

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
  {"stat", cmd_stat},
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
        int fd = open(params[1], O_CREAT | O_EXCL, 0644); 
        if (fd < 0){
            perror("Could not create file");
        }
        else {
            close(fd);
        }
        return;
    }
    else if (paramN == 1){
        if (mkdir(params[0], 0755) < 0){
            perror("Could not create directory");
        }
        return;
    }
    invalid_param();
}

int get_param (char* param, int curr_options)
{
    if (!strcmp(param, "-long") && curr_options & P_LONG)
        return P_LONG;
    if (!strcmp(param, "-acc") && curr_options & P_ACC)
        return P_ACC;
    if (!strcmp(param, "-link") && curr_options & P_LINK)
        return 4;

    return -1;
}

void print_stat_legend (int options)
{
    if (options & P_ACC){
        printf("    last access    ");
    }
    else if (options & P_LONG){
        printf("    last change    ");
    }
    if (options & P_LONG){
        printf(" links  inode     own     grp      mode   ");
    }
    printf("      size  name");
    printf("\n");
}

void print_time (time_t time)
{
    char str_time[100];
    strftime(str_time, 36, "%d-%m-%Y %H:%M:%S", localtime(&time));
    printf("%s", str_time);
}

void print_type (mode_t type)
{
    if (S_ISREG(type))
        printf("-");
    else if (S_ISDIR(type))
        printf("d");
    else if (S_ISCHR(type))
        printf("c");
    else if (S_ISBLK(type))
        printf("b");
    else if (S_ISFIFO(type))
        printf("p");
    else if (S_ISLNK(type))
        printf("l");
    else if (S_ISSOCK(type))
        printf("s");
    else
        printf("?");
}

void print_mode (mode_t mode)
{
    mode & S_IRUSR ? printf("r") : printf("-");
    mode & S_IWUSR ? printf("w") : printf("-");
    mode & S_IXUSR ? printf("x") : printf("-");

    mode & S_IRGRP ? printf("r") : printf("-");
    mode & S_IWGRP ? printf("w") : printf("-");
    mode & S_IXGRP ? printf("x") : printf("-");

    mode & S_IROTH ? printf("r") : printf("-");
    mode & S_IWOTH ? printf("w") : printf("-");
    mode & S_IXOTH ? printf("x") : printf("-");
}

void print_link (char* file)
{
    const int max_size = 500;
    char symlink[max_size];
    int link_size = readlink(file, symlink, max_size);
    if (link_size < 0){
        perror("\nCould not get symbolic link"); 
        return;
    }

    symlink[link_size] = '\0';
    printf(" -> %s", symlink);
}

void print_owner (uid_t usr)
{
    struct passwd *usr_name = getpwuid(usr);
    printf("%7s ", usr_name->pw_name);
}

void print_group (gid_t grp)
{
    struct group *grp_name = getgrgid(grp);
    printf("%7s   ", grp_name->gr_name);
}

void print_stats (char* file, int options)
{
    struct stat info;
    if (lstat(file, &info) < 0){
        printf("Couldn't get file stats for %s: %s\n", file,
                strerror(errno));
        return;
    }

    if (options & P_ACC){
        print_time(info.st_atime);
    } else if (options & P_LONG){
        print_time(info.st_mtime);
    }
    if (options & P_LONG){
        printf("%4lu %8lu ", info.st_nlink,
                                    info.st_ino);
        print_owner(info.st_uid);
        print_group(info.st_gid);
        print_type(info.st_mode);
        print_mode(info.st_mode);
    }
    printf("%10ld  %s", info.st_size, file);

    if (options & P_LINK && S_ISLNK(info.st_mode)){
        print_link(file);
    }
    printf("\n");
}

void cmd_stat (int paramN, char* params[])
{
    int options = 0;
    for (; *idx < max_params && *idx < paramN; (*idx)++){
        int new_option = get_param(params[*idx], options);
        if (new_option < 0)
            break;
        options |= new_option;
    }
    if (idx == paramN){
        missing_param();
        return;
    }

    print_stat_legend(options);

    while (idx < paramN){
        print_stats(params[idx++], options);
    }
}

int get_permissions (const char* file)
{
    if (!access(file, W_OK))
        return 1;
    if (!access(file, R_OK))
        return 2;
    if (!access(file, X_OK))
        return 2;
    /* if (!access(file, F_OK)) */
    /*     printf("Cannot access file: not enought permissions\n"); */

    perror("Cannot access file");
    return -1;
}    

void delete_file (const char* file)
{
    int can_delete = get_permissions(file);
    if (can_delete < 0) return;
    /* if (can_delete == 2){ */
    /*     printf("Delete write protected file?: (y/N): "); */
    /* } */
        
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
        nftw (params[i], recursive_delete, 10, FTW_DEPTH | FTW_PHYS);
    }
}
