#include "main.h"
#include <stdlib.h>

char *_getenv(char *name)
{
        int flag = 0, j, i;
	char *ptrenv;

        for (i = 0; environ[i]; i++)
        {
                for (j = 0; environ[i][j] != '='; j++)
                {
                                if (name[j] != environ[i][j])
				{
                                        flag = 0;
                                        break;
				}
                                else
                                        flag = 1;
                }
                if (flag == 1)
		{
			ptrenv = environ[i];
                        return (ptrenv + j + 1);
		}
        }
        return NULL;
}

