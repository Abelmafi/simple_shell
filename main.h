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
 * @status: status flag.
 * @counter: excution step counter.
 * @_environ: enviroment vector array.
 * @pid: pid var.
 *
 */
typedef struct data
{
	char **av;
	/*char *inputString;*/
	/*char **args;*/
	char **_environ;
	int status;
	int counter;
	char *pid;
} data_shell;
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

void shell_loop(data_shell *dataSH);
char *read_line(int *i);
void free_data(data_shell *datash);
void set_data(data_shell *dataSH, char **av);
void arrange_line(char **input, size_t *size, char *buffer, size_t index);
int get_line(char **input, size_t *size, FILE *stream);
/*char *get_line(data_shell *dataSH, FILE *stream);*/
/*int takeInput(char *str);*/
/*int execArgs(char **parsed, data_shell *dataSH);*/
/*int processString(data_shell *dataSH, char *str);*/
/*int systemCommand(char **parsed, data_shell *dataSH);*/

char *allocate_array(char *p, int n);
char **allocate_Darray(char **parsedArgs, int n);

int exec_line(data_shell *datash);

/* cmd_exec.c */
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
/*char *read_line(void);*/

/*int processString(char *str, status_t *flag);*/
/*int processString(data_shell *dataSh, char *str);*/
/*int _strchr(char *str, char c);*/
/*int processSpace(char *str, data_shell *dataSH);*/
/*int process_Mcmd(char *str, char **striped);*/
/*int process_And(char *str, char **striped);*/
/*int process_Ored(char *str, char **striped);*/

void chd(char **parsed);
char *_which(char *cmdLine, char **_environ);

/*char *_getenv(char *name);*/
char *_getenv(const char *name, char **_environ);
/*void _setenv(char **parsed);*/
/*void _printenv(char **parsed);*/
int _printenv(data_shell *dataSH);
void _unsetenv(char **parsed);
void _exittt(char **parsed);

/* HELPER FUNCTIONS */
int _strcmp(const char *str1, const char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
size_t _strlen(char *c);
char *_strdup(char *src);
char *_itoa(int i);

#endif

