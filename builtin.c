#include "main.h"

/**
 * cdfun - implement cd function
 * @command: array contains cd with new directory
 * Return: 0 if success, 1 if failed, 2 if directory wan't found
*/

int cdfun(char **command)
{
	char *pwd = NULL, *old = NULL;

	if (!command[1])
		return (1);
	if (strcmp(command[1], "-") == 0)
	{
		old = _getenv_("OLDPWD");
		pwd = _getenv_("PWD");

		if (!old || !pwd)
		{
			return (1);
		}
		if (chdir(old) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: can't cd to %s\n", command[0], command[1]);
			return (2);
		}
		printf("%s\n", old);
		goto setting;
	}
	else if (chdir(command[1]) == -1)
	{
		fprintf(stderr, "./hsh: 1: can't cd to %s\n", command[1]);
		return (2);
	}
	pwd = _getenv_("PWD");
	if (!pwd)
		return (1);
setting:
	setenv("OLDPWD", pwd, 1);
	setenv("PWD", command[1], 1);
	return (0);
}

/**
 * exitfun - implement the exit command
 * @command - arguments of command exit
 * @Return: exit status if it was set, 0 otherwise
*/

int exitfun(char **command)
{
	int status;

	if (!command[1])
	{
		free_command(command);
		exit(exit_stat);
	}
	status = atoi(command[1]);
	if (isNumber(command[1]) == 0)
	{
		fprintf(stderr,"./hsh: 1: exit: Illegal number: %s\n",command[1]);
		return(2);
	}
	if (command[1] && status >= 0)
	{
		free_command(command);
		exit(status);
	}
	else
		fprintf(stderr,"./hsh: 1: exit: Illegal number: %s\n",command[1]);
	return(2);
}

/**
 * envfun - print the env variables
 * @args - command arr of str
 * Return: 0 if success, 1 otherwise
*/

int envfun(char **args)
{
	char **env = environ;
	unsigned long int i;

	(void)args;

	if (!env)
		return (1);
	for (i = 0; env[i]; i++)
		printf("%s\n", env[i]);
	return (0);
}
