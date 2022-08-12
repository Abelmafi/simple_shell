#include "main.h"

/**
 * set_data - set data stricture data.
 * @dataSH: data stricture.
 * @av: argument vectore.
 *
 * Return: nothing.
 */
void set_data(data_shell *dataSH, char **av)
{
	unsigned int i;
	(void)av;

	dataSH->av = av;
	/*dataSH->inputString = NULL;*/
	/*dataSH->args = NULL;*/
	dataSH->status = 0;
	dataSH->counter = 1;
	for (i = 0; environ[i]; i++)
		;
	dataSH->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
		dataSH->_environ[i] = _strdup(environ[i]);
	dataSH->_environ[i] = NULL;
	dataSH->pid = _itoa(getpid());
}
/**
 * main - main function.
 * @ac: argument counter.
 * @av: argument array.*
 * Return: zero on failure.
 *
 */
int main(int ac, char **av)
{
	data_shell dataSH;
	(void)ac;

	set_data(&dataSH, av);
	shell_loop(&dataSH);
	/*free_data(&dataSH);*/
	return (0);
}

/**
 * shell_loop - loop function.
 * @dataSH: data stricture.
 *
 * Return: nothing.
 */
void shell_loop(data_shell *dataSH)
{
	int i = 1, index = 1;
	char *inputString;

	while (index == 1)
	{
		write(STDIN_FILENO, "$", 1);
		inputString = read_line(&i);
		if (i != -1)
		{
			if (inputString == NULL)
				continue;
			index = processString(dataSH, inputString);
			dataSH->counter += 1;
			free(inputString);
		}
		else
		{
			index = 0;
			free(inputString);
		}
	}
}

