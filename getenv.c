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