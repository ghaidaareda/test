#include "main.h"

int is_builtin(char **argv)
{
	char *builtin_functions_list[] = {"cd"};
	int (*my_builtin_func[])(char **) = {&my_cd};
	long unsigned int i;

	if (argv[0] == NULL)
	{
		return (-1);
	}
	for (i = 0; i < sizeof(builtin_functions_list) / sizeof(char *); i++)
	{
		if(strcmp(argv[0], builtin_functions_list[i]) == 0)
		{
			return (my_builtin_func[i](argv));
		}
	}
	return (execute_command(argv));
}
