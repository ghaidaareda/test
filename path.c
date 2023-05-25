#include "main.h"

/**
 * which_like - get path of the command
 * @command : command entered by user
 *
 * Return: path if exist or NULL if not
 */

char *which_like(char *command)
{
	char *path_cp, *token;
	char *path;
	int command_len, path_len, original_path_len;
	char *fullpath;

		path = _getenv("PATH");
		command_len = strlen(command);
		original_path_len = _strlen(path);
		path_cp = malloc(sizeof(char) * original_path_len + 1);
		if (path_cp == 	NULL)
		{
			perror("cant malloc path cp");
			return (NULL);
		}
		strcpy(path_cp, path);
		token = strtok(path_cp, ":");
		if (token == NULL)
		{
			token = strtok(NULL, ":");
		}
		while (token != NULL)
		{
			path_len = strlen(token);
			fullpath = malloc(sizeof(char) * (path_len + command_len) + 2);
			if (fullpath == NULL)
			{
				perror("cant malloc path cp");
                        	return (NULL);
			}
			strcpy(fullpath, token);
			fullpath[path_len] = '/';
			strcpy(fullpath + path_len + 1, command);
			fullpath[path_len + command_len + 1] = '\0';
			if (access(fullpath, X_OK) != 0)
			{
				free(fullpath);
				fullpath = NULL;
				token = strtok(NULL, ":");
			}
			else
				break;
		}
	free(path_cp);
	return (fullpath);
}
/**
 * _getenv - function to get to environment variables
 * @var : path
 *
 * Return: environ if exist, null if not
 */

char *_getenv(const char *var)
{
	int index, len;

	len = strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (strncmp(var, environ[index], len) == 0)
			return (environ[index]);
	}

	return (NULL);
}
