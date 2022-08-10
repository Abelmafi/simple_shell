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

	src_size = strlen(src);
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
