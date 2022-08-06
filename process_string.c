#include "main.h"
/**
 *
 *
 *
 *
 *
 *
 */
int processString(char *str)
{
        char **striped;
        int  piped = 0, i = 0;

        striped = (char **)malloc(sizeof(char *) * 20);
        piped = process_Mcmd(str, striped);

        if (piped)
        {
                while (i < piped)
                {
                        processSpace(striped[i]);
                        i++;
                }
        }
        else
                processSpace(str);

        return 1;
}
int process_Mcmd(char *str, char **striped)
{
        char *token;
        int bufsize = 20, position = 0;

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
        striped[position] = NULL;
        if (striped[1] == NULL)
                return 0;
        else
                return position;
}
int processSpace(char *str)
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
        execArgs(parsed);
        return 1;
}

