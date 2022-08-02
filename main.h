#ifndef MAIN_H_
#define MAIN_H_

int takeInput(char *str);
int execArgs(char **parsed);
//int processString(char* str, char** parsed);
int systemCommand(char **parsed);
char *allocate_array(char *p, int n);
char **allocate_Darray(char **parsedArgs, int n);
int allocate(char **parsed, int n);
char *lsh_read_line(void);
int processString(char *str);
int processSpace(char *str);
int process_Mcmd(char *str, char **striped);
#endif

