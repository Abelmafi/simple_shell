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
#include <signal.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define BUFSIZE 1024

/**
 * struct data - holds program data.
 * @av: argument vectore.
 * @inputString: input string array.
 * @args: argument holding array.
 * @status: status flag.
 * @counter: excution step counter.
 *
 */
typedef struct data
{
	/*char **av;*/
	/*char *inputString;*/
	/*char **args;*/
	int status;
	int counter;
} data_shell;
/**
 * struct status - holds excution status flag.
 * @flg: excution status int flag.
 *
 */

void shell_loop(data_shell *dataSH);
char *read_line(int *i);
void set_data(data_shell *dataSH, char **av);
void arrange_line(char **input, size_t *size, char *buffer, size_t index);
int get_line(char **input, size_t *size, FILE *stream);
/*char *get_line(data_shell *dataSH, FILE *stream);*/
/*int takeInput(char *str);*/
int execArgs(char **parsed, data_shell *dataSH);
int processString(data_shell *dataSH, char *str);
int systemCommand(char **parsed);

char *allocate_array(char *p, int n);
char **allocate_Darray(char **parsedArgs, int n);

/*char *read_line(void);*/

/*int processString(char *str, status_t *flag);*/
/*int processString(data_shell *dataSh, char *str);*/
int _strchr(char *str, char c);
int processSpace(char *str, data_shell *dataSH);
int process_Mcmd(char *str, char **striped);
int process_And(char *str, char **striped);
int process_Ored(char *str, char **striped);

void chd(char **parsed);
char *_which(char *cmdLine);

char *_getenv(char *name);
void _setenv(char **parsed);
void _printenv(char **parsed);
void _unsetenv(char **parsed);
void _exittt(char **parsed);

/* HELPER FUNCTIONS */
int _strcmp(const char *str1, const char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
size_t _strlen(char *c);
char *_strdup(char *src);

#endif

