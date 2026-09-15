#include "main.h"

/**
 * main - entry point for simple shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child;
	int status, i;
	char *args[1024];

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		/* Parse input directly into args array */
		args[0] = strtok(line, " \t\r\n");
		if (args[0] == NULL)
			continue;

		i = 1;
		while ((args[i] = strtok(NULL, " \t\r\n")) != NULL)
			i++;

		/* Execute command */
		child = fork();
		if (child == -1)
		{
			perror(av[0]);
			continue;
		}

		if (child == 0)
		{
			if (execve(args[0], args, environ) == -1)
				perror(av[0]);
			free(line);
			exit(1);
		}

		wait(&status);
	}

	free(line);
	return (0);
}
