#include "main.h"

/**
 * start_shell - the UNIX command line interpreter.
 * @av : pass arguments
 * @env : path
 *
 * Return: void
 */

int start_shell(char **env)
{
        char *lineptr = NULL, *delim = " \t\n\r";
        char *fullpath;
        int i = 0;
        char **token;
        int token_num;
        int builtin_status, flag, child_status;

        signal(SIGINT, handler);

        while (1)
        {
                write(1, "shell$ ", 7);
                lineptr  = _getline();
                if (lineptr == NULL)
                {
                        free(lineptr), exit(EXIT_FAILURE);
                }
                if (*lineptr != '\n')
                {
                        token = parse_input(lineptr,delim, &token_num);
                        if (i > 0 && token[i] != NULL && _strcmp(token[i], "#") == 0)
                                {
                                        token[i] = '\0';
                                }
                        builtin_status = execute_builtin_command(token, env, fullpath);
                        if (builtin_status == 0 || builtin_status == -1)
                {
                        free(fullpath);
                        free(lineptr);
                }
                if (builtin_status == 0)
                        continue;
                if (builtin_status == -1)
                        exit(EXIT_SUCCESS);
                }
                flag = 0;
                fullpath = which_like(token[0]);
                if (fullpath == NULL)
                        fullpath = token[0];
                else
                        flag = 1;
                child_status = execute_external_command(fullpath, token, env);
                if (child_status == -1)
                {
                        perror("Error");
                        break;
                }
                free (token);
                free (lineptr);
                free (fullpath);
                if (flag == 1)
                        free(fullpath);

        }

return(0);
}

#include "main.h"

/**
 * parse_input - to divid command into tokens
 * @line : command
 * @delim : string containing the delimiters.
 * @token_num : tokens count
 *
 * Return: tokens
 */

char **parse_input(char *line, const char *delim, int *token_num)
{
        char *token;
        char **argument;
        int i;
        char *line_copy;
        size_t n = strlen(line) + 1;
        *token_num = 0;
        line_copy = malloc(sizeof(char) * n);
        if (line_copy == NULL)
        {
                exit(EXIT_FAILURE);
        }
        strcpy(line_copy, line);
        token = strtok(line, delim);
        while (token != NULL)
        {
                (*token_num)++;
                token = strtok(NULL, delim);
        }
        (*token_num)++;
        argument = malloc(sizeof(char *) * (*token_num));
        token = strtok(line_copy, delim);
        for (i = 0; token != NULL; i++)
        {
                argument[i] = malloc(sizeof(char) * (strlen(token) + 1));
                if (argument[i] == NULL)
                {
                        perror("memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
                strcpy(argument[i], token);
                token = strtok(NULL, delim);
        }
        argument[i] = NULL;
        return (argument);
}
