#include "main.h"

/**
 * __findenv - returns pointer to value linked to name and sets
 * offset to be the offset of name/value in environ array
 * @name: name of env
 * @offset: offset of name/value
 * Return: pointer to value of name and offset
*/

char *_findenv_(const char *name, int *offset)
{
        int len, i;
        const char *np;
        char **p, *cp;

        if (name == NULL || environ == NULL)
                return (NULL);
        for (np = name; *np && *np != '='; ++np)
                ;
        len = np - name;
        for (p = environ; (cp = *p) != NULL; ++p)
        {
                for (np = name, i = len; i && *cp; i--)
                        if (*cp++ != *np++)
                                break;
                if (i == 0 && *cp++ == '=')
                {
                        *offset = p - environ;
                        return (cp);
                }
        }
        return (NULL);
}

/**
 * _getenv_ - get environment of name
 * @name: pointer to what we'll get its env
 * @Return: enviorment
*/

char *_getenv_(const char *name)
{
        int offset;

        return (_findenv_(name, &offset));
}

/**
 * getpath - find full path in directories
 * @name: name of program
 * Return: string conatins full path, otherwise NULL
*/

char *getpath(const char *name)
{
        char *pathenv = _getenv_("PATH");
        struct stat st;
        char *full_path, *delim = ":";
        char *token;

        if (!pathenv)
                return (NULL);
        if (stat(name, &st) == 0)
                return ((char *)name);
        token = strtok(pathenv, delim);
        while (token)
        {
                full_path = (char *)malloc(strlen(token) + strlen(name) + 2);
                if (!full_path)
                {
                        perror("./hsh: ");
                        return (NULL);
                }
                strcpy(full_path, token);
                strcat(full_path, "/");
                strcat(full_path, name);
                if (stat(full_path, &st) == 0)
                {
                        return (full_path);
                }
                free(full_path);
                token = strtok(NULL, delim);
        }
        return (NULL);

}