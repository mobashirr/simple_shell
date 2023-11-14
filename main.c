#include "main.h"

int exit_stat = 0;
/**
 * main - entry
 * Return: 0
*/
int main(void)
{
	char *line = NULL, **tokens = NULL;
	size_t len = 0;
	const char *prompt = "shell $ ";
	long unsigned int envo = length(environ);

	while(1)
	{
		if(isatty(STDIN_FILENO) != 0)
			write(1, prompt, _strlen(prompt));

		if(getline(&line,&len,stdin) == -1)
			break;

		tokens = parse(line);
		if(tokens[0])
			exit_stat = execfun(tokens);
		
		if(tokens)
			free(tokens);
	}
	if(line)
		free(line);
	if(envo != length(environ))
		free(environ);
	exit(exit_stat);

	return (0);
}

/**
 * length - to calculate length of string
 * @array: string
 * @Return: the length
*/
size_t length(char **array)
{
	size_t length = 0;

	while (array[length++])
		;
	return (length);
}

