#include "func.h"

/**
 * execbul - execute builtin functions
 * @args: string contains the command
 * Return: status of command, -1 if none
*/

int execbul(char **args)
{
        if (strcmp(args[0], "cd") == 0)
                return (cdfun(args));
        else if (strcmp(args[0], "exit") == 0)
                return (exitfun(args));
        else if (strcmp(args[0], "env") == 0)
                return (envfun(args));
        else if (strcmp(args[0], "setenv") == 0)
                return (_setenv_(args[1], args[2], 1));
        else if (strcmp(args[0], "unsetenv") == 0)
                return (_unsetenv_(args[1]));
        return (-1);
}

/**
 * execfun - to execute command
 * @args: string contain commands
 * Return: status of command executed if any, 1 otherwise
*/

int execfun(char **args)
{
        int status = 0, built;
        pid_t pid;
        struct stat st;
        char **env = environ, *path;

        if (!args)
                return (1);
        built = execbul(args);
        if (built != -1)
                return (built);
        pid = fork();
        if (pid > 0)
        {
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		return (WEXITSTATUS(status));
        }
        else if (pid == 0)
        {
                path = getpath(args[0]);
                if(!path)
                {
                free(path);
                fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
                free_command(args);
                exit(127);
                }
                if (stat(path, &st) == 0)
                {
                        if (execve(path, args, env) == -1)
                        {
                                perror("./hsh: ");
                                free_command(args);
                                        exit(2);
                        }
                        free(path);
                        free_command(args);
                        exit(126);
                }
        }
        return (1);
}
