#ifndef MAIN_H_
#define MAIN_H_

extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>

/**
 * struct status - holds excution status flag.
 * @flg: excution status int flag.
 *
 */
typedef struct status
{
	int flg;
} status_t;

int takeInput(char *str);
int execArgs(char **parsed, status_t *flag);
/*int processString(char* str, char** parsed);*/
int systemCommand(char **parsed);

char *allocate_array(char *p, int n);
char **allocate_Darray(char **parsedArgs, int n);

char *read_line(void);

int processString(char *str, status_t *flag);
int _strchr(char *str, char c);
int processSpace(char *str, status_t *flag);
int process_Mcmd(char *str, char **striped);
int process_And(char *str, char **striped);
int process_Ored(char *str, char **striped);

void chd(char **parsed);
char *_which(char *cmd);

char *_getenv(char *name);
void _setenv(char **parsed);
void _printenv(char **parsed);
void _unsetenv(char **parsed);
void _exittt(char **parsed);
#endif

