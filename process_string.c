#include "main.h"

/**
 * processString - process && || and ; tags.
 *
 * @str: string input to be processed.
 * @dataSH: excution status identigier flag.
 *
 * Return: one.
 */
int processString(data_shell *dataSH, char *str)
{
	char **striped;
	unsigned int counter = 0, status;

	dataSH->status = 0;
	striped = (char **)malloc(sizeof(char *) * 100);
	if (_strchr(str, '|'))
	{
		process_Ored(str, striped);
		do {
			status = processSpace(striped[counter], dataSH);
			counter++;
		} while (striped[counter] && dataSH->status == 10);
	}
	else if (_strchr(str, '&'))
	{
		process_And(str, striped);
		while (striped[counter] && dataSH->status == 0)
		{
			status = processSpace(striped[counter], dataSH);
			counter++;
		}
	}
	else if (_strchr(str, ';'))
	{
		process_Mcmd(str, striped);
		while (striped[counter])
		{
			status = processSpace(striped[counter], dataSH);
			counter++;
		}
	}
	else
		status = processSpace(str, dataSH);
	free(striped);
	if (!status)
		return (0);
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
 * @dataSH: output string array.
 * Return: no of strings.
 */
int processSpace(char *str, data_shell *dataSH)
{
	char **parsed;
	char *token;
	int pos = 0, status;

	parsed = (char **)malloc(sizeof(char *) * BUFSIZE);
	token = strtok(str, " ");
	while (token != NULL)
	{
		parsed[pos] = token;
		pos++;
		if (pos >= BUFSIZE)
			parsed = allocate_Darray(parsed, BUFSIZE + 20);
		token = strtok(NULL, " ");
	}
	parsed[pos] = NULL;
	if (parsed[0] == NULL)
		return (1);
	status = execArgs(parsed, dataSH);
	if (!status)
		return (0);
	return (1);
}

