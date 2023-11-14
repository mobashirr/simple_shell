#include "main.h"

/**
 * _realloc_ - reallocate memory for array
 * @array: array to be reallocted for
 * @size: new size
 * @Return: pointer to new allocated memory
*/

void *_realloc_(void *ptr, size_t size)
{
        void *new = NULL;

        if (size)
        {
                if (!ptr)
                        return (malloc(size));
                new = malloc(size);
                if (new)
                {
                        memcpy(new, ptr, size);
                        free(ptr);
                }
        }
        return (new);
}

/**
 * free_command - free allocated memory for array
 * @arr: string array
*/
void free_command(char **arr)
{
        if (arr[0])
                free(arr[0]);
        if (arr)
                free(arr);
        arr = NULL;
}