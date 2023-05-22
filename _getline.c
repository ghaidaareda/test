#include "main.h"
/**
 *
 *
 */
char *_getline(void)
{
    static char buffer[1024];
    static int pos = 0;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        buffer[pos++] = c;
        if (pos >= 1024) {
            printf("Error: input too long\n");
            return NULL;
        }
    }
    if (c == EOF)
    {
        write(1, "\n", 1);
    }

    if (pos == 0 && c == EOF) {
        return NULL;
    }
    if (buffer[pos-1] == '\n') {
        write(1, "\n", 1);
    }

    buffer[pos] = '\0';
    pos = 0;
    return buffer;
}
