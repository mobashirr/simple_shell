#include "main.h"

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The difference between the ASCII values of the first
 *         non-matching characters in the strings.
 */
int _strcmp(const char *s1, const char *s2)
{
	if(!s1 || !s2)
		return(1);

	while (*s1 && s2 && (*s1 == *s2))
	{
        	s1++;
        	s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strlen - to get length of string
 * @str: string to process
 * Return: length of str
 */

int _strlen(const char *str)
{
	const char *s;

	for (s = str; *s; ++s)
		;
	return (s - str);
}
/**
 * isNumber - Check if a string is a valid number.
 * @str: The input string to check.
 * Return: 1 if the string is a number, 0 otherwise.
 */
int isNumber(const char *str) 
{
	char *endptr;
	strtol(str, &endptr, 10);  /* Base 10 for decimal integers */

	if (*endptr != '\0') 
        return 0;

	return 1;
}

/**
 * replaceOrRemove - self explantory
 * @str: string
 * @target: char
*/

void replaceOrRemove(char str[], char target)
{
	int length = _strlen(str), i;

	for (i = 0; i < length; i++)
	{
		if (str[i] == target)
		{
			if (i < length - 1)
				str[i] = str[i + 1];
			else
				str[i] = '\0';
		}
	}
}
