#include "main.h"
/**
 * allocate_array - allocate memory space fot pointer array.
 * @ptr: input pointer.
 * @n: space byte required.
 *
 * Return: new allocated memory space.
 */

char *allocate_array(char *ptr, int n)
{
	return (realloc(ptr, n * sizeof(char)));
}
/**
 * allocate_Darray - allocate memory space for double pointer array.
 * @parsedArgs: input double pointer.
 * @n: space byte required.
 *
 * Return: new allocated memory space.
 */
char **allocate_Darray(char **parsedArgs, int n)
{
	return ((char **)realloc(parsedArgs, n * sizeof(char *)));
}
