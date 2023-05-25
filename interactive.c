#include "main.h"

/**
 * start_shell - the UNIX command line interpreter.
 * @av : pass arguments
 * @env : path
 *
 * Return: void
 */

void start_shell(char **av, char **env)
{
	char *lineptr = NULL, *delim = " \t\n\r";
	int i = 0;
	char *argument[MAX_ARGU];
	char *fullpath;

	signal(SIGINT, handler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "shell$ ", 7);
		lineptr  = _getline();
		if (lineptr == NULL)
		{
			return;
		}
		if (*lineptr != '\n')
		{
			i = 0;
			argument[i] = _strtok(lineptr, delim);
			if (argument[i] == NULL)
			{
				start_shell(argument, env);
			}
			while (argument[i])
			{
				if (i > 0 && argument[i] != NULL && _strcmp(argument[i], "#") == 0)
				{
					argument[i] = '\0';
				}
				argument[++i] = _strtok(NULL, delim);
			}
			execute_builtin_command(argument, env, av, fullpath);
		}
	}
	free(lineptr);
}
