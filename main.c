#include "main.h"

/**
* main - check main
*
* Return: void
*
*/
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t char_read;

	printf("simple_shell:");


	char_read = getline(&buffer, &bufsize, stdin);

}
