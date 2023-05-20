#include "main.h"

void read_input(char **lineptr, size_t *n) 
{
	ssize_t char_num;
	char_num = getline(lineptr, n, stdin);
	if (char_num == -1)
       	{
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
	}
}

char **parse_input(char *line, const char *delim, int *token_num)
{
	char *token;
	int i;
	char **argv = NULL;
	char *line_copy;
	size_t n = strlen(line) + 1;

	*token_num = 0;
	line_copy = malloc(sizeof(char) * n);
	if (line_copy == NULL)
	{
		perror("memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	strcpy(line_copy, line);
	token = strtok(line, delim);
	while (token != NULL)
	{
		(*token_num)++;
		if (strcmp(token, "cd") == 0)
		{
			is_builtin(argv);
		}
		token = strtok(NULL, delim);
	}
	(*token_num)++;
	argv = malloc(sizeof(char*) * (*token_num));
	if (argv == NULL)
	{
	    perror("memory allocation error\n");
	    exit(EXIT_FAILURE);
	}
	*token_num = 0;
	strcpy(line_copy, line);
	token = strtok(line_copy, delim);
	for (i = 0; token != NULL; i++)
	{
		if (strcmp(token, "cd") == 0)
		{
			is_builtin(argv);
			argv[i] = NULL;
		}
		else
		{
        	argv[i] = malloc(sizeof(char) * (strlen(token) + 1 ));
        	if (argv[i] == NULL)
		{
			perror("memory allocation error\n");
			exit(EXIT_FAILURE);
		}
		strcpy(argv[i], token);
		}
		(*token_num)++;
        token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	return argv;
}
int execute_command(char **argv)
{

	pid_t child;
	if (argv[0] == NULL)
	{
	return 0;
	}
	if (exit_command(argv))
	{
		exit_shell();
	}
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
	{
		execute(argv);
		printf("%s: No such file or directory\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else 
	{
		wait(NULL);
	}
	return (0);
}
void cleanup(char **argv, char *lineptr, char *lineptr_copy)
{
	free(lineptr_copy);
	free(lineptr);
	if (argv != NULL) {
        int i;
        for (i = 0; argv[i] != NULL; i++) {
            free(argv[i]);
        }
        free(argv);
    }
}

int main(int ac, char **argv)
{
	char *shell_prompt = "our_shell$ ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	const char *delim = " \n";
	int token_num;
	int interactive_mode = isatty(STDIN_FILENO);
	(void)ac;

	if (interactive_mode)
	{
	while (1)
	{
		printf("%s", shell_prompt);
		read_input(&lineptr, &n);
			if (*lineptr != '\n')
			{
				lineptr_copy = strdup(lineptr);
				argv = parse_input(lineptr, delim, &token_num);
				execute_command(argv);
			}
	}
}
	cleanup(argv, lineptr, lineptr_copy);
	return 0;
}
