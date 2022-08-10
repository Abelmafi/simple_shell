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
/**
 * _strcmp - compaire two strings.
 * @str1: string input.
 * @str2: second string input.
 *
 * Return: 1 if they are same and 0 if they are not.
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0' || *str2 == '\0')
			break;
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
		return (0);
	else
		return (1);
}
/**
 * _strcat - cat sourse string to destination string.
 *
 * @dest: destination string.
 * @src: sourse string.
 * Return: destination pointer.
 */
char *_strcat(char *dest, char *src)
{
	int i, j, z;

	i = _strlen(dest);
	j = _strlen(src);
	for (z = 0; z < j; z++)
		dest[z + i] = src[z];
	dest[i + j] = '\0';
	return (dest);
}
/**
 * _strlen - calculate string length.
 * @c: string input.
 *
 * Return: length of string.
 */
size_t _strlen(char *c)
{
	char *e = c;

	while (*e)
		e++;
	return (e - c);
}
/**
 * _strcpy - copy sourse string to destination string.
 * @dest: destination string.
 * @src: sourse string.
 * Return: destination pointer.
 */
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	if (dest == NULL)
		return (NULL);
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ptr);
}


