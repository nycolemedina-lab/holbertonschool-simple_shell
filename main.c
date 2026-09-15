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
	char *cmd;
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

		/* Extract the command token, ignoring spaces, tabs, and newlines */
		cmd = strtok(line, " \t\r\n");
		if (cmd == NULL)
			continue;

		child = fork();
		if (child == -1)
		{
			perror(av[0]);
			free(line);
			exit(1);
		}

		if (child == 0)
		{
			args[0] = cmd;
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
