#include "main.h"
/**
 * get_line - read command line arguments from standard input.
 * @input: input string holding array poiner.
 * @size: array size.
 * @stream: opop
 * Return: input size on success and -1 on failerity.
 */
ssize_t get_line(char **input, size_t *size, FILE *stream)
{
	int i;
	static ssize_t position;
	ssize_t tmp;
	char c = 'z', *buffer;

	if (position == 0)
		fflush(stream);
	else
		return (-1);
	position = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (!buffer)
		return (-1);
	while (1)
	{
		i = read(STDIN_FILENO, &c, 1);
		if (i == -1 || (i == 0 && position == 0))
		{	free(buffer);
			return (-1);	}
		if (i == 0 && position != 0)
		{	buffer++;
			break;	}
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			arrange_line(input, size, buffer, position);
			tmp = position;
			if (i != 0)
				position = 0;
			return (tmp);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= BUFSIZE)
			buffer = _realloc(buffer, position, position + 1);
	}
	return (0);
}
/**
 * read_line - read line mid function.
 * @ie: sign index.
 * Return: zero on failure.
 *
 */
char *read_line(int *ie)
{
	char *input = NULL;
	size_t bufsize = 0;

	*ie = get_line(&input, &bufsize, stdin);
	return (input);
}
/**
 * arrange_line - arrange input string array size according to
 * buffer size.
 * @input: input string array.
 * @size: input string size.
 * @buffer: buffer string array.
 * @index: buffer size.
 * Return: Nothing.
 */
void arrange_line(char **input, size_t *size, char *buffer, size_t index)
{
	if (*input == NULL || *size < index)
	{
		if (index > BUFSIZE)
			*size = index;
		else
			*size = BUFSIZE;
		*input = buffer;
	}
	else
	{
		_strcpy(*input, buffer);
		free(buffer);
	}
}

