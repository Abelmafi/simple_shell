#include "main.h"
/**
 * _strchr - search character inside string.
 *
 * @str: input string.
 * @c: character to be searched.
 * Return: 1 in sucess and 0 on failure.
 */
int _strchr(char *str, char c)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (c == '|' || c == '&')
		{
			if (str[i] == c && str[i + 1] == c)
				return (1);
		}
		if (c == ';')
		{
			if (str[i] == c)
				return (1);
		}
	}
	return (0);
}

