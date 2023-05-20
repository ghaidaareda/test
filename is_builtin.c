#include "main.h"
int my_cd(char **args);
int is_builtin(char **argv)
{
	char *builtin_functions_list[] = {"cd"};
	long unsigned int i;

	if (argv == NULL || argv[0] == NULL)
	{
		return (-1);
	}
	for (i = 0; i < sizeof(builtin_functions_list) / sizeof(char *); i++)
	{
		if(strcmp(argv[0], "cd") == 0)
		{
			return (my_cd(argv));
		}
	}
	return (execute_command(argv));
}
