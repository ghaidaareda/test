#include "main.h"

void read_input(char **lineptr, size_t *n) 
{
    ssize_t char_num;
   char_num = getline(lineptr, n, stdin);
    if (char_num == -1) {
        perror("Exit\n");
        exit(EXIT_FAILURE);
    }
}

char **parse_input(char *line, const char *delim, int *token_num) {
    char *token;
    int i;
    char **argv;
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
    while (token != NULL) {
        (*token_num)++;
        token = strtok(NULL, delim);
    }
    (*token_num)++;
    argv = malloc(sizeof(char*) * (*token_num));
    token = strtok(line_copy, delim);
    for (i = 0; token != NULL; i++) {
        argv[i] = malloc(sizeof(char) * strlen(token));
        if (argv[i] == NULL) {
            perror("memory allocation error\n");
            exit(EXIT_FAILURE);
        }
                        strcpy(argv[i], token);
        token = strtok(NULL, delim);
    }
    argv[i] = NULL;
    return argv;
}

void execute_command(char **argv) {
        pid_t child;
    if (is_builtin(argv)) {
        exit_shell();
    }
    child = fork();
    if (child == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child == 0) {
        execute(argv);
        printf("%s: No such file or directory\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

void cleanup(char **argv, char *lineptr, char *lineptr_copy) {
    free(argv);
    free(lineptr_copy);
    free(lineptr);
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
    if (interactive_mode) {
        while (1) {
            printf("%s", shell_prompt);
            read_input(&lineptr, &n);
            lineptr_copy = strdup(lineptr);
            argv = parse_input(lineptr, delim, &token_num);
            execute_command(argv);
        }
    }
    cleanup(argv, lineptr, lineptr_copy);
    return 0;
}
