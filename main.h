#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <paths.h>
#include <stdbool.h>
#include <alloca.h>
#include <sys/stat.h>
#include <string.h>

#define LINEBUF 1024
#define ARGBUF  64
#define DELIMIT " \t\n"

extern char **environ;
extern int exit_stat;

char    **parse(char *);
int	parse_var(char **args);

int     execfun(char **);
int     execbul(char **);
int     cdfun(char **);
int     exitfun(char **);
int     envfun(char ** );
int	_unsetenv_(const char *);
int _setenv_(const char *name, const char *value, int rewrite);
char    *_findenv_(const char *name, int *offset);
char    *_getenv_(const char *name);
char	*getpath(const char *, char *env[]);
void	*_realloc_(void *, size_t size);
int	_strcmp(const char *, const char *);
int	isNumber(const char *); 
int	_strlen(const char *);

/*not used yet:*/
void	free_command(char **arr);
char 	*_getenv2(char *name, char *env[]);

#define BUILTIN_NUM ((sizeof(builtins)) / (sizeof(builtin)))
#endif
