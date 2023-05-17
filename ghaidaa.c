int main(int argc, char **argv) {
    char *shell_prompt = "our_shell$ ";
    char *lineptr = NULL, *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t char_num;
    const char *delim = " \n";
    int token_num = 0;
    char *token;
    int i;
    pid_t child;
    int interactive_mode = isatty(STDIN_FILENO); // check if running in interactive mode
    (void) argc;

    if (!interactive_mode) { // non-interactive mode
        if (argc < 2) {
            fprintf(stderr, "Usage: %s scriptfile\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        FILE *scriptfile = fopen(argv[1], "r");
        if (scriptfile == NULL) {
            perror("Error opening scriptfile");
            exit(EXIT_FAILURE);
        }
        while ((char_num = getline(&lineptr, &n, scriptfile)) != -1) {
            lineptr[strcspn(lineptr, "\n")] = '\0';
            lineptr_copy = strdup(lineptr);
            token = strtok(lineptr, delim);
            while (token != NULL) {
                token_num++;
                token = strtok(NULL, delim);
            }
            token_num++;
            char **args = malloc(sizeof(char*) * token_num);
            token = strtok(lineptr_copy, delim);
            for (i = 0; token != NULL; i++) {
                args[i] = strdup(token);
                token = strtok(NULL, delim);
            }
            args[i] = NULL;
            if (!is_builtin(args)) {
                child = fork();
                if (child == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else if (child == 0) {
                    execute(args);
                    printf("%s: command not found\n", args[0]);
                    exit(EXIT_FAILURE);
                } else {
                    wait(NULL);
                }
            }
            free(args);
            free(lineptr_copy);
            token_num = 0;
            lineptr = NULL;
            n = 0;
        }
        fclose(scriptfile);
        exit(EXIT_SUCCESS);
    }

    while (1) { // interactive mode
        printf("%s", shell_prompt);
        char_num = getline(&lineptr, &n, stdin);
        if (char_num == -1) {
            if (feof(stdin)) {
                exit(EXIT_SUCCESS);
            } else {
                perror("error in reading");
                exit(EXIT_FAILURE);
            }
        }
        lineptr[strcspn(lineptr, "\n")] = '\0';
        lineptr_copy = strdup(lineptr);
        token = strtok(lineptr, delim);
        while (token != NULL) {
            token_num++;
            token = strtok(NULL, delim);
        }
        token_num++;
        char **args = malloc(sizeof(char*) * token_num);
        token = strtok(lineptr_copy, delim);
        for (i = 0; token != NULL; i++) {
            args[i] = strdup(token);
            token = strtok(NULL, delim);
        }
        args[i] = NULL;
        if (!is_builtin(args)) {
            child = fork();
            if (child == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (child == 0) {
                execute(args);
                printf("%s: command not found\n", args[0]);
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
            }
        }
        free(args);
        free(lineptr_copy);
        token_num = 0;
        lineptr = NULL;
        n = 0;
    }

    return 0;
}
