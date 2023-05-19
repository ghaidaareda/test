#include "main.h"
/*
 *
 *
 */
int my_cd(char **args)
{
	char *cwd;

	if (chdir(args[1]) == 0)
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
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		setenv("PWD", cwd, 1);
		free(cwd);
	}
	else
	{
	perror("cd: could not get current directory\n");
        return (-1);
    	}
	return(0);
}
