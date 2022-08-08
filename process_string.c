#include "main.h"

/**
 * processString - process && || and ; tags.
 *
 * @str: string input to be processed.
 * @flag: excution status identigier flag.
 *
 * Return: one.
 */
int processString(char *str, status_t *flag)
{
	char **striped;
	unsigned int counter = 0;

	flag->flg = 0;
	striped = (char **)malloc(sizeof(char *) * 100);
	if (_strchr(str, '|'))
	{
		process_Ored(str, striped);
		do {
			processSpace(striped[counter], flag);
			counter++;
		} while (striped[counter] && flag->flg == 10);
	}
	else if (_strchr(str, '&'))
	{
		process_And(str, striped);
		while (striped[counter] && flag->flg == 0)
		{
			processSpace(striped[counter], flag);
			counter++;
		}
	}
	else if (_strchr(str, ';'))
	{
		process_Mcmd(str, striped);
		while (striped[counter])
		{
			processSpace(striped[counter], flag);
			counter++;
		}
	}
	else
		processSpace(str, flag);
	free(striped);
	return (1);
}

/**
 * process_Mcmd - process string according to ";" tag.
 *
 * @str: input string array.
 * @striped: output string array.
 * Return: no of strings.
 */
int process_Mcmd(char *str, char **striped)
{
	char *token;
	int bufsize = 100, position = 0;

	token = strtok(str, ";");
	while (token != NULL)
	{
		striped[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += 20;
			striped = allocate_Darray(striped, bufsize);
			if (!striped)
			{
				perror("\ncould not allocate space");
				exit(0);
			}
		}
		token = strtok(NULL, ";");
	}
	if (striped[1] == NULL)
		return (0);
	striped[position] = NULL;
	return (position);
}

/**
 * process_Ored - process string according "||" tag.
 * @str: input string array.
 * @striped: output string array.
 *
 * Return: no of strings.
 */
int process_Ored(char *str, char **striped)
{
	char *token;
	int bufsize = 20, position = 0;

	token = strtok(str, "||");
	while (token != NULL)
	{
		striped[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 20;
			striped = allocate_Darray(striped, bufsize);
			if (!striped)
			{
				perror("\ncould not allocate space");
				exit(0);
			}
		}
		token = strtok(NULL, "||");
	}
	if (striped[1] == NULL)
		return (0);
	striped[position] = NULL;
	return (position);
}

/**
 * process_And - process string according to "&&" tag.
 * @str: input string array.
 * @striped: output string array.
 *
 * Return: no of strings.
 */
int process_And(char *str, char **striped)
{
	char *token;
	int bufsize = 20, position = 0;

	token = strtok(str, "&&");
	while (token != NULL)
	{
		striped[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 20;
			striped = allocate_Darray(striped, bufsize);
			if (!striped)
			{
				perror("\ncould not allocate space");
				exit(0);
			}
		}
		token = strtok(NULL, "&&");
	}
	if (striped[1] == NULL)
		return (0);
	striped[position] = NULL;
	return (position);
}

/**
 * processSpace - process string accoriding to " " tag.
 * @str: input string array.
 * @flag: output string array.
 * Return: no of strings.
 */
int processSpace(char *str, status_t *flag)
{
	char **parsed;
	char *token;
	int bufsize = 20, position = 0;

	parsed = (char **)malloc(sizeof(char *) * bufsize);
	if (!parsed)
	{
		perror("Lsh: memory allocation error");
		exit(EXIT_FAILURE);
	}
	token = strtok(str, " ");
	while (token != NULL)
	{
		parsed[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += 20;
			parsed = allocate_Darray(parsed, bufsize);
			if (!parsed)
			{
				perror("\ncould not allocate space");
				exit(0);
			}
		}
		token = strtok(NULL, " ");
	}
	parsed[position] = NULL;
	execArgs(parsed, flag);
	return (1);
}

