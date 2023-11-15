#include "main.h"

/**
 * _setenv_ - set name to value
 * @name: name of env
 * @value: value of new env
 * @rewrite: if set replace any current value
 * @Return: 0 if success, -1 otherwise
*/

int _setenv_(const char *name, const char *value, int rewrite)
{
	static char **lastenv;
	char *C;
	int l_value, offset;
	const char *originalName;
	const char *originalValue;
	if(!name || !value)	/*if no name return 2 invalid option*/
		return(2);

	if (*value == '=')
		++value;
	l_value = _strlen(value);
	if ((C = _findenv_(name, &offset)))
	{
		if (!rewrite)
			return (0);
		if ((int)_strlen(C) >= l_value)
		{
			while ((*C++ = *value++))
				;
			return (0);
		}
	}
	else
	{
		size_t cnt;
		char **P;
		
		for (P = environ; *P != NULL; P++)
			;
		cnt = P - environ;
		P = (char **)_realloc_(lastenv, sizeof(char *) * (cnt + 2));
		if (!P)
			return (-1);
		if (lastenv != environ)
			memcpy(P, environ, cnt * sizeof(char *));
		lastenv = environ = P;
		offset = cnt;
		environ[cnt + 1] = NULL;
	}

originalName = name;
originalValue = value;
for (; *name && *name != '='; ++name)
    ;

if (!(environ[offset] = malloc((size_t)((name - originalName) + l_value + 2))))
    return (1);

name = originalName;
C = environ[offset];

for (; (*C = *name++) && *C != '='; ++C)
    ;

for (*C++ = '='; (*C++ = *originalValue++);)
    ;

	return (0);
}

/**
 * _unsetenv_ - unset enviorn
 * @name: name to be unset
 * @Return: 0 if success, -1 otherwise
*/

int _unsetenv_(const char *name)
{
	char **P;
	int offset;

	while (_findenv_(name, &offset))
	{
		for (P = &environ[offset];; ++P)
			if (!(*P = *(P + 1)))
				break;
	}
	return (0);
}
