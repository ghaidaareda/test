#include "main.h"
void exit_shell()
{
    printf("Exiting shell...\n");
    fflush(stdout);
    exit(0);
}

int is_builtin(char **argv){
    return strcmp(argv[0], "exit") == 0;
}
