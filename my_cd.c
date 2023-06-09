#include "main.h"
#include <limits.h>
/*
 *
 *
 */
int my_cd(char **argument)
{
	char cwd[PATH_MAX];

	if (argument == NULL || argument[0] == NULL || strcmp(argument[0], "cd") != 0)
       	{
		return (-1);
	}
	if (argument[1] == NULL || strcmp(argument[1], "~") == 0)
                {
                        chdir(getenv("HOME"));
                }
	 else if (strcmp(argument[1], "-") == 0)
                {
                        if (getenv("OLDPWD") != NULL)
                        {
                                chdir(getenv("OLDPWD"));
                        }
			else
                        {
                                fprintf(stderr, "cd: OLDPWD not set\n");
                                return (-1);
                        }
		}
	else
	{
		if(chdir(argument[1]) == -1)
        {
                perror("cd");
                return (-1);
        }
	}
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
                return (-1);
        }
	printf("%s\n", cwd);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
	return(0);
}
