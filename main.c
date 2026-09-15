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
	char *token;

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

		/* Extract all command words/arguments into args array */
		token = strtok(line, " \t\r\n");
		if (token == NULL)
			continue;

		i = 0;
		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " \t\r\n");
			i++;
		}
		args[i] = NULL;

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
