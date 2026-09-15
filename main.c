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
		/* Print prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &len, stdin);

		/* Handle Ctrl+D / EOF */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		/* Strip the newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Ignore empty lines */
		if (line[0] == '\0')
			continue;

		/* Create child process */
		child = fork();
		if (child == -1)
		{
			perror(av[0]);
			free(line);
			exit(1);
		}

		if (child == 0)
		{
			args[0] = line;
			args[1] = NULL;

			if (execve(args[0], args, environ) == -1)
			{
				perror(av[0]);
				free(line);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
