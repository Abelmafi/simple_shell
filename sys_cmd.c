#include "main.h"
/**
 * systemCommand - system linux comand operator function.
 *
 * @parsed: input string array.
 *
 * Return: one in success and 0 on failure.
 */

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
			return (0);
		case 2:
			chd(parsed);
			return (1);
		case 3:
			_printenv(parsed);
			return (1);
		case 4:
			_setenv(parsed);
			return (1);
		case 5:
			_unsetenv(parsed);
			return (1);
		default:
			break;
	}
	return (0);
}
/**
 * _exittt - exit function with exit status.
 *
 * @parsed: input command string.
 * Return: aloways nothing.
 */
void _exittt(char **parsed)
{
	if (parsed[1] == NULL)
		_exit(0);
	else
		_exit(atoi(parsed[1]));
}
/**
 * chd - exit function with exit status.
 *
 * @parsed: input command string.
 * Return: aloways nothing.
 */

void chd(char **parsed)
{
	if (parsed[1] == NULL)
		parsed[1] = "$HOME";
	if (strcmp(parsed[1], "-") == 0)
		parsed[1] = "..";
	if(chdir(parsed[1]) < 0)
	{
		write(1, "bash: cd: ", 10);
		perror(parsed[1]);
	}
}

