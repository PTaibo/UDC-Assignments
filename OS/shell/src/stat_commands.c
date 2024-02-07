/*
 * Name: Siyuan He              Login: siyuan.he
 * Name: Paula Taibo Suárez     Login: p.taibo
 */

#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include "stat_commands.h"

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
#include <dirent.h>

#include "types.h"
#include "colors.h"
#include "list.h"
#include "error_msgs.h"
#include "help_pages.h"

// Define command parameter bitmasks
#define P_LONG 1
#define P_ACC 2
#define P_LINK 4
#define P_RECA 8
#define P_RECB 16
#define P_HID 32

struct cmd stat_commands[] = {
    {"stat", cmd_stat},
    {"list", cmd_list},
    {NULL, NULL}
};

int check_stat_commands (int paramN, char* command[])
{
    for (int i = 0; stat_commands[i].name != NULL; i++){
        if (!strcmp(command[0], stat_commands[i].name)){
            if (!is_help_param(paramN, command))
                (*stat_commands[i].funct)(paramN, command+1);
            return 1;
        }
    }
    return 0;
}

int get_param (char* param, int curr_options)
{
    if (!strcmp(param, "-long") && !(curr_options & P_LONG))
        return P_LONG;
    if (!strcmp(param, "-acc") && !(curr_options & P_ACC))
        return P_ACC;
    if (!strcmp(param, "-link") && !(curr_options & P_LINK))
        return P_LINK;
    if (!strcmp(param, "-hid") && !(curr_options & P_HID))
        return P_HID;
    if (!strcmp(param, "-reca") && !(curr_options & P_RECA)
            && !(curr_options & P_RECB))
        return P_RECA;
    if (!strcmp(param, "-recb") && !(curr_options & P_RECB)
            && !(curr_options & P_RECA))
        return P_RECB;

    return -1;
}

void print_stat_legend (int options)
{
    printf(YELLOW);
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
    printf(RESET_CLR);
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
    mode & S_IXUSR ? printf("x") :
        mode & S_ISUID ? printf("s") : printf("-");

    mode & S_IRGRP ? printf("r") : printf("-");
    mode & S_IWGRP ? printf("w") : printf("-");
    mode & S_IXGRP ? printf("x") :
        mode & S_ISGID ? printf("s") : printf("-");

    mode & S_IROTH ? printf("r") : printf("-");
    mode & S_IWOTH ? printf("w") : printf("-");
    mode & S_IXOTH ? printf("x") :
        mode & S_ISVTX ? printf("t") : printf("-");
}

void print_link (const char* file)
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
    if (usr_name == NULL){
        printf(RED "%7s " RESET_CLR, "ERROR");
        return;
    }
    printf("%7s ", usr_name->pw_name);
}

void print_group (gid_t grp)
{
    struct group *grp_name = getgrgid(grp);
    if (grp_name == NULL){
        printf(RED "%7s   " RESET_CLR, "ERROR");
        return;
    }
    printf("%7s   ", grp_name->gr_name);
}

void print_stats (const char* file, int options)
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

int get_options (int max_params, int paramN, int *idx, char* params[])
{
    int options = 0;
    for (; *idx < max_params && *idx < paramN; (*idx)++){
        int new_option = get_param(params[*idx], options);
        if (new_option < 0)
            break;
        options |= new_option;
    }
    return options;
}

void cmd_stat (int paramN, char* params[])
{
    int idx = 0;
    int options = get_options(3, paramN, &idx, params);

    if (idx == paramN){
        missing_param();
        return;
    }

    print_stat_legend(options);

    while (idx < paramN){
        print_stats(params[idx++], options);
    }
}

int print_single_file (int options, basic_list* dir_list,
                       char* file)
{
    int is_dir = 0;

    if ((options & P_HID) || file[0] != '.'){
        struct stat file_info;
        lstat(file, &file_info);
        if (S_ISDIR(file_info.st_mode)){
            printf(CYAN);
            if (dir_list != NULL){
                basicList_append(file, dir_list);
                is_dir++;
            }
        }
        print_stats(file, options);
        printf(RESET_CLR);
    }
    return is_dir;
}

int print_dir_stats (struct dirent *file, int options,
                     DIR* root, basic_list* dir_list)
{
    char cwd[MAX_COMMAND_SIZE];
    getcwd(cwd, MAX_COMMAND_SIZE);
    printf(GREEN "%s\n" RESET_CLR, cwd);
    print_stat_legend(options);

    int dirN = 0;

    while (file != NULL){
        dirN += print_single_file(options, dir_list, file->d_name);
        file = readdir(root);
    }
    return dirN;
}

void open_dir (char* dir, int options);

void recurs_subdirs (int dirN, basic_list* dir_list,
                     int options)
{
    for (int i = 0; i < dirN; i++){
        char dir[MAX_COMMAND_SIZE];
        basicList_getter(i, dir, dir_list);
        if (!strcmp(dir, ".") || !strcmp(dir, ".."))
            continue;
        open_dir(dir, options);
    }
}

void recurs_after (struct dirent *file,
                   int options, DIR* root)
{
    basic_list dir_list;
    basicList_initialize(&dir_list);

    int dirN = print_dir_stats(file, options, root, &dir_list);

    recurs_subdirs(dirN, &dir_list, options);
    basicList_clear(&dir_list);
}

void print_file_list (int options, int fileN, basic_list *flist)
{
    char cwd[MAX_COMMAND_SIZE];
    getcwd(cwd, MAX_COMMAND_SIZE);
    printf(GREEN "%s\n" RESET_CLR, cwd);
    print_stat_legend(options);

    for (int i = 0; i < fileN; i++){
        char file[MAX_COMMAND_SIZE];
        basicList_getter(i, file, flist);

        print_single_file(options, NULL, file);
    }
}

void recurs_before(struct dirent *file,
                   int options, DIR* root)
{
    basic_list file_list;
    basicList_initialize(&file_list);

    int fileN = 0;

    while (file != NULL){
        struct stat file_info;
        lstat(file->d_name, &file_info);
        if (S_ISDIR(file_info.st_mode) &&
        strcmp(file->d_name, ".") &&
        strcmp(file->d_name, ".."))
            open_dir(file->d_name, options);

        basicList_append(file->d_name, &file_list);
        fileN++;

        file = readdir(root);
    }
    
    print_file_list(options, fileN, &file_list);
    basicList_clear(&file_list);
}

void read_dir (char* dir, int options, DIR* root)
{
    struct dirent *base_dir = readdir(root);

    if (base_dir == NULL){
        if (errno == 0) return;
        cannot_open_dir();
    }
    chdir(dir);

    if (options & P_RECA){
        recurs_after(base_dir, options, root);
    } else if (options & P_RECB){
        recurs_before(base_dir, options, root);
    } else {
        print_dir_stats(base_dir, options, root, NULL);
    }
}


void open_dir (char* dir, int options)
{
    DIR *root = opendir(dir);
    if (root == NULL){
        cannot_open_dir();
        return;
    }
    errno = 0;

    read_dir(dir, options, root);

    closedir (root);

    chdir("..");
}

void cmd_list (int paramN, char* params[])
{
    int idx = 0;
    int options = get_options(5, paramN, &idx, params);
    
    if (idx == paramN){
        missing_param();
        return;
    }

    for (; idx < paramN; idx++){
        if (access(params[idx], F_OK)){
            cannot_open_file();
            continue;
        }
        char cwd[MAX_COMMAND_SIZE];
        getcwd(cwd, MAX_COMMAND_SIZE);
        open_dir(params[idx], options);
        chdir(cwd);
    }
}

