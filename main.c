#include "main.h"

/**
 * main - the main function for our simple shell
 *
 * Return: 0(sucess) or error msg(error)
 * @ac:arguments count
 * @argv:arguments variables
 */

int main(int ac, char **argv)
{
	char *shell_prompt = "our_shell$ ";
	char *lineptr = NULL; char *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t char_num;
	const char *delim = " \n";
	int token_num = 0;
	char *token;
	int i;
	pid_t child;
	(void) ac;
	while (5)
	{
		printf("%s", shell_prompt);
		char_num = getline(&lineptr, &n, stdin);
		if (char_num == -1)
		{
			printf("Exit\n");
			return (-1);
		}
		lineptr_copy = malloc(sizeof(char) * char_num);
		if (lineptr_copy == NULL)
		{
			printf("memory allocation error\n");
				return (-1);
		}
		strcpy(lineptr_copy, lineptr);
		token = strtok(lineptr, delim);
		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, delim);
		}
		token_num++;
		argv = malloc(sizeof(char*) * token_num);
		token = strtok(lineptr_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		child = fork();
                if (child == -1)
                {
                        free(lineptr), exit(EXIT_FAILURE);
                }
                if (child == 0)
                {
		execute(argv); 
		printf("%s: No such file or directory\n", argv[0]);
                }
                else
                {
                        wait(NULL);
                }
		getenv("PATH");
	}
		free(argv);
                free(lineptr_copy);
                free(lineptr);
	return (0);
}
