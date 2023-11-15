#include "main.h"

int _setenv_(const char *name, const char *value, int rewrite)
{
        static int allocated;
        char *C;
        int l_value, offset;
        char ***envp = &environ;

        if (!name || !value || !rewrite)
                return (0);
        if (*value == '=')
                ++value;
        l_value = strlen(value);
        if ((C = _findenv_(name, &offset)))
        {
                if ((int)strlen(C) >= l_value)
                        while ((*C++ = *value++))
                                return (0);
        }
        else
        {
                int cnt;
                char **p;

                for (p = *envp, cnt = 0; *p; ++p, ++cnt)
                        ;
                if (allocated)
                {
                        *envp = (char **)_realloc_((char *)*envp, (size_t)(sizeof(char *)*(cnt +2)));
                        if (!*envp)
                                return (-1);
                }
                else
                {
                        allocated = 1;
                        p = malloc((size_t)(sizeof(char *)*(cnt + 2)));
                        if (!p)
                                return (-1);
                        memcpy(p, *envp, cnt * sizeof(char *));
                        *envp = p;
                }
                (*envp)[cnt + 1] = NULL;
                offset = cnt;
        }
        for (C = (char *)name; *C && *C != '='; ++C)
                ;
        if (!((*envp)[offset] = malloc((size_t)((int)(C - name) + l_value + 2))))
                return (-1);
        for (C = (*envp)[offset]; (*C = *name++) && *C != '='; ++C)
                ;
        for (*C++ = '='; (*C++ = *value++);)
                ;
        return (0);
}

int _unsetenv_(const char *name)
{
        char **envp = environ, **p;
        int offset;

        while (_findenv_(name, &offset))
                for (p = &envp[offset];; ++p)
                        if (!(*p = *(p + 1)))
                                break;
        return (0);
}