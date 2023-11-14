#include "main.h"

/**
 * parse - to parse the input line
 * @line: the line parsed
 * Return: array of splitted command
*/

char **parse(char *line)
{
        int len = 0, cap = ARGBUF;
        char *token, **tokens;

        tokens = malloc(cap * sizeof(char *));
        if (!tokens)
        {
                perror("./hsh: ");
                return (NULL);
        }
        token = strtok(line, DELIMIT);
        while (token)
        {
                tokens[len++] = token;
                if (len >= cap)
                {
                        cap += (ARGBUF + 1);
                        tokens = _realloc_(tokens, cap * sizeof(char *));
                        if (!tokens)
                        {
                                perror("./hsh: ");
                                return (NULL);
                        }
                }
                token = strtok(NULL, DELIMIT);
        }
        tokens[len] = NULL;
        parse_var(tokens);
        return (tokens);
}

/**
 * parse_var - replaces variables if there
 * @args: the input tokens
 * Return: 0 if success, otherwise 1
*/

int parse_var(char **args)
{
        int i, j, k = 1, l;
        pid_t pid = getpid();
        char *env_var;

        for (i = 0; args[i]; i++)
        {
                for (j = 0; args[i][j]; j++)
                {
                        if (args[i][j] == '$' && args[i][j + 1] == '$')
                        {
                                sprintf(args[i] + j, "%d", pid);
                                k = 0;
                        }
                        else if (args[i][j] == '$' && args[i][j + 1] == '?')
                        {
                                sprintf(args[i] + j, "%d", exit_stat);
                                k = 0;
                        }
                        else if (args[i][0] == '#') /*Handle comments*/
                        {
                                args[i][0] = '\0';
                                for (l = i + 1; args[l]; l++)
                                        args[l] = NULL;
                                return (0);
                        }
                        else if (args[i][j] == '$' && args[i][1] != '$'
                                                && args[i][1] != '?')
                        {
                                env_var = _getenv_(args[i] + 1);
                                if (env_var && args[i][0] == '$')
                                {
                                        strcpy(args[i], env_var);
                                }
                                else
                                        args[i][j] = '\0';
                                k = 0;
                        }
                        else if (args[i][j] == '\\')
                        {
                                /*char ch;
                                ch = args[i][j + 1]; */
                                sprintf(args[i] + j, "%s", args[i] + j + 1);
                        }
                }
        }

        return (k);
}