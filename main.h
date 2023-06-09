#ifndef MAIN_h_
#define MAIN_h_

#define MAX_ARGU 1024

#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


extern char **environ;

void execute_command(char** argument, char** env, char* av[]);
int start_shell(char **env);
char *which_like(char *command);
void execute(char**argv);
char *_getenv(const char *name);
void print_env(void);
void _puts(char *s);
void execute_command(char **argument, char **env, char *av[]);
char **split_line(char *line, const char *delim);
void _echo(void);
char *_getline(void);
int my_cd(char **argument);
void handler(int sig __attribute__((unused)));
int execute_builtin_command(char **argument, char **env, char *fullpath);
int execute_external_command(char *fullpath, char **token, char **env);
void non_interactive(char **av, char **env);
char **parse_input(char *line, const char *delim, int *token_num);
/**string functions */

char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strncat(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
unsigned int _strspn(char *s, char *accept);
char *_strdup(char *str);
void _puts(char *s);
char *_strcat(char *dest, char *src);

char *_strtok(char *line, char *delim);


#endif
