#include "main.h"
/**
 * execArgs - excute parsed linux comand along with arguments.
 * @parsed: comand line and argiments.
 * @dataSH: excution status flag.
 *
 * Return: one on success.
 */
int execArgs(char **parsed, data_shell *dataSH)
{
	pid_t pid;
	char *cmd;
	int wstatus, i = 0;

	if (systemCommand(parsed))
		return (1);
	cmd = _which(parsed[0]);
	if (cmd == NULL)
	{
		while (parsed[0][i])
			i++;
		write(2, parsed[0], i + 1);
		write(2, ": command not found\n", 20);
		dataSH->status = 10;
		return (1);
	}
	if (access(cmd, X_OK) < 0)
	{	perror(cmd);
		return (1);	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (execve(cmd, parsed, environ) < 0)
		{	perror(parsed[0]);
			exit(10);	}
		exit(0);
	}
	if (waitpid(pid, &wstatus, 0) == -1)
		exit(1);
	if (!WIFEXITED(wstatus))
		exit(1);
	dataSH->status = WEXITSTATUS(wstatus);
	free(parsed);
	return (1);
}
/**
 * _which - search comand lines inside PATH env variable.
 * @cmdLine: command string to be searched inside PATH.
 *
 * Return: the directory whery the comand line found or null.
 */
char *_which(char *cmdLine)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd;
	struct stat st;

	path = _getenv("PATH");
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmdLine);
		token_path = strtok(ptr_path, ":");
		/*i = 0;*/
		while (token_path != NULL)
		{
			/*if (is_cdir(path, &i))*/
			if (stat(cmdLine, &st) == 0)
				return (cmdLine);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmdLine);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmdLine, &st) == 0)
			return (cmdLine);
		return (NULL);
	}
	if (cmdLine[0] == '/')
		if (stat(cmdLine, &st) == 0)
			return (cmdLine);
	return (NULL);
}
