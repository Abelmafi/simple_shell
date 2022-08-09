#include "main.h"
/**
 * execArgs - excute parsed linux comand along with arguments.
 * @parsed: comand line and argiments.
 * @flag: excution status flag.
 *
 * Return: one on success.
 */
int execArgs(char **parsed, status_t *flag)
{
	pid_t pid;
	char *cmd;
	int wstatus;

	if (parsed[0] == NULL)
		return (1);
	if (systemCommand(parsed))
		return (0);
	cmd = _which(parsed[0]);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (execve(cmd, parsed, environ) < 0)
		{
			perror(parsed[0]);
			exit(10);
		}
		exit(0);
	}
	if (waitpid(pid, &wstatus, 0) == -1)
		exit(1);
	if (!WIFEXITED(wstatus))
		exit(1);
	flag->flg = WEXITSTATUS(wstatus);
	free(parsed);
	return (1);
}
/**
 * _which - search comand lines inside PATH env variable.
 * @cmd: command string to be searched inside PATH.
 *
 * Return: the directory whery the comand line found or null.
 */
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
			if (stat(cmd, &st) == 0)
				return (cmd);
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
/*int dir_check(char *path, int *n)
{
	if (path[*n] == ':')
		return (1);
	while (path[*n] !=*/
