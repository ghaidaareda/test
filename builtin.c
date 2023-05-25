#include "main.h"

/**
 * execute_external_command - executes external commands
 * @argument: command arguments
 * @env: environment variables
 * @av: argument vector
 *
 * Return: void
 */
int execute_external_command(char *fullpath, char **token, char **env)
{
	pid_t child_pid;
	int child_status;

	if (fullpath == NULL)
	{
		write(STDERR_FILENO,"./hsh: No such file or directory\n", 34);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(command_path);
	       	exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(fullpath, token, env) == -1)
		{
			perror(0);
			free(fullpath);
			exit(errno);
		}
	}
	else
		waitpid(child_pid, &child_status, WUNTRACED);
	return (0);
}

/**
 * execute_builtin_command - executes builtin commands
 * @argument: command arguments
 * @env: environment variables
 * @av: argument vector
 *
 * Return: void
 */
void execute_builtin_command(char **argument, char **env, char *av[])
{
	if (argument == NULL || argument[0] == NULL)
	{
		return;
	}
	else if (_strcmp("echo", argument[0]) == 0 && _strcmp("$$", argument[1]) == 0)
	{
		_echo();
		return;
	}
	else if (_strcmp("env", argument[0]) == 0)
	{
		print_env();
		return;
	}
	else if (_strcmp(argument[0], "exit") == 0)
	{
		exit(0);
	}
	else if (_strcmp(argument[0], "#") == 0)
	{
		return;
	}
	else if (_strcmp("cd", argument[0]) == 0)
	{
		my_cd(argument);
		return;
	}
	else
	{
		execute_external_command(fullpath, token, env);
	}
}
