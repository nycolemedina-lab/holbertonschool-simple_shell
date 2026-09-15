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
	int status;
	char *args[2];

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

		/* Grab ONLY the first word as the executable command path */
		args[0] = strtok(line, " \t\r\n");
		if (args[0] == NULL)
			continue;
		args[1] = NULL;

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
