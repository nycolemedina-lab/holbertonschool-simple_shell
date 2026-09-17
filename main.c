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
	int status, i, last_status = 0;
	char *args[1024];
	char *token;
	char *cmd_path;

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
			exit(last_status);
		}

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

		/* Built-in: exit */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(last_status);
		}

		/* Find command in PATH before forking */
		cmd_path = find_in_path(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], cmd_count, args[0]);
			last_status = 127;
			continue;
		}

		child = fork();
		if (child == -1)
		{
			perror(av[0]);
			free(cmd_path);
			continue;
		}

		if (child == 0)
		{
			if (execve(cmd_path, args, environ) == -1)
				perror(av[0]);
			free(cmd_path);
			free(line);
			exit(1);
		}

		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);

		free(cmd_path);
	}

	free(line);
	return (last_status);
}
