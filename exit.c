#include "main.h"

void exit_shell()
{
    printf("Exiting shell...\n");
    fflush(stdout);
    exit(0);
}

int exit_command(char **argv)
{
    return strcmp(argv[0], "exit") == 0;
}
