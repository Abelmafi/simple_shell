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
		*dup_offset = *src;
		dup_offset++;
		src++;
	}
	*dup_offset = '\0';
	return (dup);
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
	return (b);
}
