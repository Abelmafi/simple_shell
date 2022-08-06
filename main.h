#ifndef MAIN_H_
#define MAIN_H_

extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int takeInput(char *str);
int execArgs(char **parsed);
/*int processString(char* str, char** parsed);*/
int systemCommand(char **parsed);
char *allocate_array(char *p, int n);
char **allocate_Darray(char **parsedArgs, int n);
int allocate(char **parsed, int n);
char *read_line(void);
int processString(char *str);
int processSpace(char *str);
int process_Mcmd(char *str, char **striped);
void chd(char **parsed);
char *_which(char *cmd);
char *_getenv(char *name);
void _setenv(char **parsed);
void _printenv(char **parsed);
void _unsetenv(char **parsed);
void _exittt(char **parsed);
#endif

