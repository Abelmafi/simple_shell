#include "main.h"
/**
 *
 *
 *
 *
 *
 */

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
	char *inputString;
	status_t flag = {0};

	while (1)
	{
		inputString = read_line();
		/*execFlag = processString(inputString, parsedArgs);*/
		/*parsedArgs  = processString(inputString);*/
		processString(inputString, &flag);
		/*if (execFlag == 1)*/
			/*execArgs(parsedArgs);*/
		free(inputString);
	}
	return (0);
}
char *read_line(void)
{
	int bufsize = 20;
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
		/*i = read(0, &c, 1);*/
		read(0, &c, 1);
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
int execArgs(char **parsed, status_t *flag)
{
	pid_t pid;
	char *cmd;
	char *envVir[] = {NULL};
	int wstatus;

	cmd = _which(parsed[0]);

	if (parsed[0] == NULL)
		return 1;
	if (systemCommand(parsed))
		return 0;
	else
		pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		if (execve(cmd, parsed, envVir) < 0)
		{
			perror("\ncould not excute command");
			exit (10);
		}
		exit(0);
	}
	if (waitpid(pid, &wstatus, 0) == -1)
		exit (1);
	if (!WIFEXITED(wstatus))
		exit (1);	
	 flag->flg = WEXITSTATUS(wstatus);
	 free(parsed);
	 return 1;
}
int systemCommand(char **parsed)
{
	char *sysCmd[5];
	int i, swhCmd = 0;

	sysCmd[0] = "exit";
	sysCmd[1] = "cd";
	sysCmd[2] = "env";
	sysCmd[3] = "setenv";
	sysCmd[4] = "unsetenv";

	for (i = 0; i < 5; i++)
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
			_exittt(parsed);
			return 0;
		case 2:
			chd(parsed);
			return (1);
		case 3:
			_printenv(parsed);
			return 1;
		case 4:
			_setenv(parsed);
			return 1;
		case 5:
			_unsetenv(parsed);
			return 1;
		default:
			break;
	}
	return (0);
}
void _exittt(char ** parsed)
{
	if (parsed[1] == NULL)
		_exit(0);
	else
		_exit(atoi(parsed[1]));
}
void chd(char **parsed)
{
	if (parsed[1] == NULL)
		parsed[1] = "$HOME";
	if (strcmp(parsed[1], "-") == 0)
		parsed[1] = "..";
	chdir(parsed[1]);
}
char *_which(char *cmd)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd;
	struct stat st;

	path = _getenv("PATH");
	if (path)
	{
		ptr_path = strdup(path);
		len_cmd = strlen(cmd);
		token_path = strtok(ptr_path, ":");
		/*i = 0;*/
		while (token_path != NULL)
		{
			/*if (is_cdir(path, &i))*/
			/*	if (stat(cmd, &st) == 0)*/
			/*		return (cmd);*/
			len_dir = strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			strcpy(dir, token_path);
			strcat(dir, "/");
			strcat(dir, cmd);
			strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
