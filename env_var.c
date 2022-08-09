#include "main.h"
/**
 * _getenv - search for environment variable by the name "name".
 * @name: name of env variable.
 *
 * Return: pointer to friest occurance of env name or null.
 */
char *_getenv(char *name)
{
	int flag = 0, j, i;
	char *ptrenv;

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (name[j] != environ[i][j])
			{
				flag = 0;
				break;
			}
			else
				flag = 1;
		}
		if (flag == 1)
		{
			ptrenv = environ[i];
			return (ptrenv + j + 1);
		}
	}
	return (NULL);
}

/**
 * _setenv - set invironment variable.
 *
 * @parsed: command line argument.
 * Return: Nothing.
 */

void _setenv(char **parsed)
{
	if (setenv(parsed[1], parsed[2], 1) < 0)
		perror(parsed[1]);
}
/**
 * _unsetenv - unset(delete) invironment variable.
 *
 * @parsed: command line argument.
 * Return: Nothing.
 */
void _unsetenv(char **parsed)
{
	int i;

	i = unsetenv(parsed[1]);
	if (i < 0)
	{
		perror("could not unset env variable");
	}
}
/**
 * _printenv - print invironment variable.
 *
 * @parsed:command line argument.
 * Return: Nothing.
 */

void _printenv(char **parsed)
{
	int i, j;

	if (parsed[1] == NULL)
	{
		for (i = 0; environ[i]; i++)
		{
			for (j = 0; environ[i][j]; j++)
				;
			write(1, environ[i], j + 1);
			write(1, "\n", 2);
		}
	}
}

