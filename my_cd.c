#include "main.h"
#include <limits.h>
/*
 *
 *
 */
int my_cd(char **args)
{
	char cwd[PATH_MAX];

	if (args == NULL || args[0] == NULL)
       	{
		return (-1);
	}
	else if (chdir(args[1]) == 0)
	{ 
		if (args[1] == NULL || strcmp(args[1], "~") == 0)
		{
			chdir(getenv("HOME"));
		}
		else if (strcmp(args[1], "-") == 0)
		{
			if (getenv("OLDPWD") != NULL)
			{
				chdir(getenv("OLDPWD"));
				return (0);
			}
			else
			{
				perror("cd: OLDPWD not set\n");
				return (-1);
			}
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (-1);
	}
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
                return (-1);
        }
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
	return(0);
}
