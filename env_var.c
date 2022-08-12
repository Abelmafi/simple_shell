#include "main.h"
/**
 * _getenv - search for environment variable by the name "name".
 * @name: name of env variable.
 * @_environ: env variable array.
 * Return: pointer to friest occurance of env name or null.
 */
char *_getenv(const char *name, char **_environ)
{
	int flag = 0, j, i;
	char *ptrenv;

	for (i = 0; _environ[i]; i++)
	{
		for (j = 0; _environ[i][j] != '='; j++)
		{
			if (name[j] != _environ[i][j])
			{
				flag = 0;
				break;
			}
			else
				flag = 1;
		}
		if (flag == 1)
		{
			ptrenv = _environ[i];
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
		perror(parsed[0]);
	}
}
/**
 * _printenv - print invironment variable.
 *
 * @dataSH:command line argument struct.
 * Return: 1 for success.
 */

int _printenv(data_shell *dataSH)
{
	int i, j;

	for (i = 0; dataSH->_environ[i]; i++)
	{
		for (j = 0; dataSH->_environ[i][j]; j++)
			;
		write(1, dataSH->_environ[i], j);
		write(1, "\n", 1);
	}
	dataSH->status = 0;
	return (1);
}

