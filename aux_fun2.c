#include "main.h"

/**
 * _strdup - duplicate input string.
 * @src: input string.
 *
 * Return: duplicated string.
 */
char *_strdup(char *src)
{
	int src_size;
	static char *dup;
	char *dup_offset;

	src_size = _strlen(src);
	dup = (char *)malloc(sizeof(char) * src_size + 1);
	if (dup == NULL)
		return (NULL);
	dup_offset = dup;
	while (*src)
	{
		*dup = *src;
		dup++;
		src++;
	}
	*dup = '\0';
	/*free(dup);*/
	return (dup_offset);
}
/**
 * _itoa - convert intiger to string.
 * @i: intiger input.
 *
 * Return: converted string.
 */
char *_itoa(int i)
{
	char const digit[] = "0123456789";
	char *p;
	static char *b;
	int shifter = i, size = 0, no;

	no = i;
	while (no < 1)
	{
		no /= 10;
		size++;
	}
	(i < 0) ? (size += 1) : (size);
	p = (char *)malloc(sizeof(char) * size + 1);
	b = p;
	if (i < 0)
	{
		*p++ = '-';
		i *= -1;
	}
	do {
		++p;
		shifter = shifter / 10;
	} while (shifter);
	*p = '\0';
	do {
		*--p = digit[i % 10];
		i = i / 10;
	} while (i);
	/*free(p);*/
	return (b);
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	int res = 0, i;

	for (i = 0; s[i] != '\0'; ++i)
	{
		res = res * 10 + s[i] - '0';
	}

	return (res);
}
/**
 * rev_string - reverses a string.
 * @string: input string.
 * Return: no return.
 */
void rev_string(char *string)
{
	char temp;
	int i, length;

	length = _strlen(string) - 1;
	for (i = 0; i < _strlen(string) / 2; i++)
	{
		temp = string[i];
		string[i] = string[length];
		string[length--] = temp;
	}
}
