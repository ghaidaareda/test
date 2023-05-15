#include  "main.h"
/** execute-to execute commands 
 * Return:void
 * @argv:command to be executed
 */
void execute(char**argv)
{
	char * command  = NULL;
	char * command_path = NULL;
	if (argv)
	{
		command = argv[0];
		command_path = which_like(command);

		if(execve(command_path, argv, NULL) == -1)
		{
			perror("ERROR");
		}
	}
}

