#include "main.h"
/**
 * read_line - read command line arguments from standard input.
 *
 * Return: string of comandlines.
 */
char *read_line(void)
{
	int bufsize = 20;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	char c;

	write(1, "\n>>", 3);
	if (!buffer)
	{
		perror("lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		read(0, &c, 1);
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;
		if (position >= bufsize)
		{
			bufsize += 20;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				perror("lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * main - main function.
 *
 * Return: zero on failure.
 *
 */
int main(void)
{
	char *inputString;
	status_t flag = {0};

	while (1)
	{
		inputString = read_line();
		processString(inputString, &flag);
		free(inputString);
	}
	return (0);
}
