#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *allocate_array(char *ptr, int n)
{
	return realloc(ptr, n * sizeof(char));
}
char **allocate_Darray(char **parsedArgs, int n)
{
	return (char **)realloc(parsedArgs, n * sizeof(char*));
}
int main()
{
	char *inputString;// **parsedArgs;
	int execFlag = 0;
	//int size = 20;

	//parsedArgs = allocate_Darray(parsedArgs, 100);
	while (1)
	{
		inputString = lsh_read_line();
		//execFlag = processString(inputString, parsedArgs);
		//parsedArgs  = processString(inputString);
		processString(inputString);
		//if (execFlag == 1)
	
			//execArgs(parsedArgs);
		if (inputString[0] != '\0')
		{
			free(inputString);
			//free(parsedArgs);
		}
	}
	return (0);
}
char *lsh_read_line(void)
{
	int bufsize = 20, i;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	char c;

	write(1, "\n>>", 3);
	if (!buffer)
  	{
		perror("lsh: allocation error\n");
		exit(EXIT_FAILURE);
 	}
	while (1)
	{
	 	i = read(0, &c, 1);
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return buffer;
		}
		else
			buffer[position] = c;
		position++;

		if (position >= bufsize)
		{
			bufsize += 20;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				perror("lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
int execArgs(char **parsed)
{
	pid_t id;

	if (parsed[0] == NULL)
		return 1;
	if (systemCommand(parsed))
		return 0;
	else
		id = fork();
	if (id == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			perror("\ncould not excute command..");
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		return 1;
	}
}
/**int processString(char *str, char **parsed)
{
	int i = 0;

	if (str[0] == '\0')
		return 1;
	while ((parsed[i] = strsep(&str, " ")) != NULL)
	{
		i++;
	}
	if (systemCommand(parsed))
		return 0;
	return (1);
}*/
int processString(char *str)
{
	char **striped;
	int  piped = 0, i = 0;

	striped = (char **)malloc(sizeof(char *) * 20);
	piped = process_Mcmd(str, striped);

	if (piped)
	{
		while (i < 3)
		{
			processSpace(striped[i]);
			i++;
		}
	}
	else
		processSpace(str);

	return 1;
}
int process_Mcmd(char *str, char **striped)
{
	char *token;
	int bufsize = 20, position = 0;

	token = strtok(str, ";");
        while (token != NULL)
        {
                striped[position] = token;
                position++;

                if (position >= bufsize)
                {
                        bufsize += 20;
                        striped = allocate_Darray(striped, bufsize);
                        if (!striped)
                        {
                                perror("\ncould not allocate space");
                                exit (0);
                        }
                }
                token = strtok(NULL, ";");
        }
	striped[position] = NULL;
	if (striped[1] == NULL)
		return 0;
	else
		return 1;
}	
int processSpace(char *str)
{
	char **parsed;
	char *token, tokens;
	int bufsize = 20, position = 0, mulCmd = 0;
	int bufsize2 = 20;

	parsed = (char **)malloc(sizeof(char *) * bufsize);
	if (!parsed)
	{
		perror("Lsh: memory allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, " ");

	while (token != NULL)
	{
		parsed[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 20;
			parsed = allocate_Darray(parsed, bufsize);
			if (!parsed)
			{
				perror("\ncould not allocate space");
				exit (0);
			}
		}
		token = strtok(NULL, " ");
	}
	parsed[position] = NULL;
	execArgs(parsed);
	return 1;
}


int systemCommand(char **parsed)
{
	char *sysCmd[2];
	int i, swhCmd = 0;
	char *username;

	sysCmd[0] = "exit";
	sysCmd[1] = "cd";
	//sysCmd[2] = "help";
	sysCmd[2] = "env";

	for (i = 0; i < 3; i++)
	{
		if (strcmp(parsed[0], sysCmd[i]) == 0)
		{
			swhCmd = i + 1;
			break;
		}
	}
	switch (swhCmd)
	{
		case 1:
			exit(0);
		case 2:
			chdir(parsed[1]);
			return (1);
		//case 3:
		//	openHelp();
		//	return (1);
		case 3:
			username = getenv("USER");
			printf("%s", username);
		default:
			break;
	}
	return (0);
}
