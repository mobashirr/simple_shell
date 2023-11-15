#include "main.h"

/**
 * my_setenv - Set or update an environment variable
 * @name: The name of the environment variable
 * @value: The value to set for the environment variable
 * @overwrite: Flag indicating whether to overwrite if the variable already exists
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv_(const char *name, const char *value, int overwrite) 
{
    if (!name || !name[0] || strchr(name, '=') || (getenv(name) && !overwrite))
        return overwrite ? 0 : -1;

    char *env_entry;
    asprintf(&env_entry, "%s=%s", name, value ? value : "");

    if (!env_entry)
        return -1;

    if (getenv(name))
        for (int i = 0; environ[i]; ++i)
            if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=') {
                free(environ[i]);
                environ[i] = env_entry;
                return 0;
            }

    int num_vars = 0;
    while (environ[num_vars])
        ++num_vars;

    char **new_environ = realloc(environ, (num_vars + 2) * sizeof(char *));
    if (!new_environ) {
        free(env_entry);
        return -1;
    }

    environ = new_environ;
    environ[num_vars] = env_entry;
    environ[num_vars + 1] = NULL;

    return 0;
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
