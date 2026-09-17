#include "main.h"

/**
 * _getenv - retrieves an environment variable
 * @name: name of the environment variable
 *
 * Return: pointer to the value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0, j;

	if (name == NULL || environ == NULL)
		return (NULL);

	while (environ[i] != NULL)
	{
		j = 0;
		while (name[j] != '\0' && environ[i][j] == name[j])
			j++;

		if (name[j] == '\0' && environ[i][j] == '=')
			return (environ[i] + j + 1);

		i++;
	}
	return (NULL);
}
