#include "main.h"

/**
 * find_in_path - searches PATH directories for an executable command
 * @command: the command typed by the user
 *
 * Return: dynamically allocated full path string on success, NULL on failure
 */
char *find_in_path(char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[1024];

	if (command == NULL || command[0] == '\0')
		return (NULL);

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env || strlen(path_env) == 0)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
