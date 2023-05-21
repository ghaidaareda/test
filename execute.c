#include "main.h"
/**
 * execute_command - execution process
 * @argument : command
 * @env : environment
 * @av : arg veector
 *
 * Return : void
 */

void execute_command(char **argument, char **env, char *av[])
{
	pid_t child_pid;
	int child_status;
	char *command_path;
	if (_strcmp("env", argument[0]) == 0)
	{
		print_env();
		return;
	}
	command_path = which_like(argument[0]);
	if (command_path == NULL)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s: %s: command not found\n", av[0], argument[0]);
		}
		else
		{
			perror(av[0]);
		}
		return;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(argument), exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(command_path, argument, env) == -1)
		{
			if (errno == ENOENT)
			{
			fprintf(stderr, "%s: %s: No such file or directory\n", av[0], argument[0]);
			}
			else
			{
				perror(av[0]);
			}
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &child_status, WUNTRACED);
		if (WIFEXITED(child_status))
		{
			if (WEXITSTATUS(child_status) != 0)
			{
				fprintf(stderr, "%s: %s: exited with status %d\n", av[0], argument[0], WEXITSTATUS(child_status));
			}
		}
	}
free(command_path);
}
