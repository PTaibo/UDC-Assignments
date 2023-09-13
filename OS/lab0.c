#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maxline instead of putting 200 directly
#define MAXLINE 200

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
  if (!strcmp(tr, "-l") || !strcmp(tr, "-n"))
      printf("logins.....\n");
  else
        printf("logins and names...\n");

void procesarComando(char * tr[])
{
  if (tr[0] == NULL){
    return;
  if (!strcmp(tr, "authors"))
    Cmd_authors(tr+1);
  else if (!strcmp(tr, "quit") || !strcmp(tr, "bye") || !strcmp(tr, "exit"))
    Cmd_quit();
  else
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
