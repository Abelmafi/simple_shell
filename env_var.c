#include "main.h"
/**
 *
 *
 *
 *
 *
 */

void _setenv(char **parsed)
{
        if (parsed[1] == NULL || parsed[2] == NULL)
        {
                perror("couldnot set the environment variable");
        }
        setenv(parsed[1], parsed[2], 1);
}
void _unsetenv(char **parsed)
{
        int i;

        i = unsetenv(parsed[1]);
        if (i < 0)
        {
                perror("could not unset env variable");
        }
}
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

