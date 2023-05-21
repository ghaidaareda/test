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

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simple_shell$ ");
		lineptr= _getline();
		if (lineptr == NULL)
		{
			write(1, "\n", 2);
			break;
		}

		if (*lineptr != '\n')
		{
			i = 0;
			argument[i] = _strtok(lineptr, delim);
			if (_strcmp("exit", argument[0]) == 0)
				break;
			while (argument[i])
				argument[++i] = _strtok(NULL, delim);
			if (_strcmp("cd", argument[0]) == 0)
                        {
                                my_cd(argument);
				start_shell(argument, env);

                        }
			else
			{			
			execute_command(argument,env,av);
			}
			
		}
	}
}
