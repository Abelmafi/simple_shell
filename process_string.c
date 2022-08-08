#include "main.h"
/**
 *
 *
 *
 *
 *
 */
int _strchr(char *str, char c)
{
	int i;
	for (i = 0; str[i]; i++)
	{
		if (c == '|' || c == '&')
		{
			if (str[i] == c && str[i + 1] == c)
				return 1;
		}
		if (c == ';')
		{
			if (str[i] == c)
				return 1;
		}
	}
	return 0;
}
		

int processString(char *str, status_t *flag)
{
        char **striped;
        int  piped = 0, ored = 0, anded = 0, result = 0;
	unsigned int counter = 0;

	flag->flg = 0;
        striped = (char **)malloc(sizeof(char *) * 100);
	if (_strchr(str, '|'))
	{
		process_Ored(str, striped);
		do
                {
                        processSpace(striped[counter], flag);
                        counter++;
                } while (striped[counter] && flag->flg == 10);
		free(striped);

	}
	else if (_strchr(str, '&'))
	{
		process_And(str, striped);
		while (striped[counter] && flag->flg == 0)
                {
                        processSpace(striped[counter], flag);
                        counter++;
                }
		free(striped);
	}
	else if (_strchr(str, ';'))
        {
		process_Mcmd(str, striped);
                while (striped[counter])
                {
                        processSpace(striped[counter], flag);
                        counter++;
                }
		free(striped);
        }
	else
	{
		processSpace(str, flag);
		free(striped);
	}
       	return 1;
}
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
                                exit (0);
                        }
                }
                token = strtok(NULL, ";");
        }
        if (striped[1] == NULL)
                return 0;
        else
	{
		striped[position] = NULL;
                return position;
	}
}
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
                                exit (0);
                        }
                }
                token = strtok(NULL, "||");
        }
        if (striped[1] == NULL)
		return 0;
        else
	{
		striped[position] = NULL;
		return position;
	}
}
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
                                exit (0);
                        }
                }
                token = strtok(NULL, "&&");
        }
        if (striped[1] == NULL)
                return 0;
        else
	{
		striped[position] = NULL;
        	return position;
	}
}
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
                                exit (0);
                        }
                }
                token = strtok(NULL, " ");
        }
	parsed[position] = NULL;
	execArgs(parsed, flag);
	return 1;
}

