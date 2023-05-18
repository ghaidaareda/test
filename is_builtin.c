#include "main.h"
/**
 *
 *
 *
 */
int is_builtin(char **args)
{
	char *builtin_functions[] = {"cd", "env", "help", "exit"};
	int (*my_builin_functions[])(char **) = {&my_cd, &my_env, &my_help, &my_exit}
