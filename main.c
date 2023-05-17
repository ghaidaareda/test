#include "main.h"

void read_input(char **lineptr, size_t *n) {
    ssize_t char_num = getline(lineptr, n, stdin);
    if (char_num == -1) {
        perror("Exit\n");
        exit(EXIT_FAILURE);
    }
    (*lineptr)[strcspn(*lineptr, "\n")] = '\0';
}

char **parse_input(char *line, const char *delim, int *token_num) {
    char *token;
    int i;
    char **argv;
    *token_num = 0;
    token = strtok(line, delim);
    while (token != NULL) {
        (*token_num)++;
        token = strtok(NULL, delim);
    }
    (*token_num)++;
    argv = malloc(sizeof(char*) * (*token_num));
    token = strtok(line, delim);
    for (i = 0; token != NULL; i++) {
        argv[i] = strdup(token);
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
