#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include <sys/types.h> */
#include <unistd.h>

// Define maxline instead of putting 200 directly
#define MAXLINE 200

struct CMD {
    char* name;
    void (*funct)(char**);
};

int trocearCadena(char* cadena, char* trozos[])
{
  int i = 1;

  if ((trozos[0]=strtok(cadena, " \n\t")) == NULL)
        return 0;
  while ((trozos[i]=strtok(NULL, " \n\t"))!=NULL)
    i++;
  return i;
}

void Cmd_quit ()
{
  exit(0);
}

void Cmd_authors(char *tr[])
{
  if (tr[0] == NULL)
    printf("logins and names...\n");
  if (!strcmp(tr[0], "-l") || !strcmp(tr[0], "-n"))
      printf("logins.....\n");
  else
        printf("logins and names...\n");
}

void Cmd_pid (char *tr[])
{
    printf("Shell0s pid is %d\n", getpid());
}

/* char* joinStr (char sl, char* s2) */
/* { */
/*     char* p; */
/*     p = malloc(strlen(s1)+strlen(s2)+1); // For '\0' (not in string length) */

/*     char p[MAX]; */
/*     ... */
/*     return p; //WRONG!!! Because p is local so you loose it in stack when you go back */
/*     //Make p static to solve problem */
/* } */

struct CMD valid_commands[]={
    {"authors", Cmd_authors},
    {"quit", Cmd_quit},
    {"exit", Cmd_quit},
    {"bye", Cmd_quit},
    {"pid", Cmd_pid},
    {NULL, NULL}
};


void procesarComando(char * tr[])
{
    int i;
    for (i=0; valid_commands[i].name != NULL; i++){
        if (!strcmp(tr[0], valid_commands[i].name)) {
                (*valid_commands[i].funct)(tr+1);
                return;
        }
    }
    printf("Command not found\n");
}

int main()
{
  /* char* line; */
  /* line = malloc(MAXLINE); */
  //Better to use an array in this situation
  
  char line[MAXLINE];
  char* tr[MAXLINE/2];

  while (1){
    printf("-->");
    fgets(line, MAXLINE, stdin);
    trocearCadena(line, tr);
    procesarComando(tr);
  }

  /* free(line); */
}
