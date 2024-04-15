#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 10 * 1024 * 1024
#define BUFSIZE 512 * 1024

FILE *Fopen(char *argv);
char *readfile(int argc, char **argv);
void zip(char *buffer);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    char *str = (char *)malloc(STRSIZE);
    str[0] = '\0';

    for (size_t i = 1; i < argc; i++)
    {
        char *temp = readfile(i, argv);

        strcat(str, temp);

        free(temp);
    }

    zip(str);

    return 0;
}

FILE *Fopen(char *argv)
{
    FILE *fp = fopen(argv, "r");
    if (fp == NULL)
    {
        printf("wzip: cannot open file\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

char *readfile(int i, char **argv)
{
    FILE *fp = Fopen(argv[i]);

    char *str = (char *)malloc(STRSIZE);
    str[0] = '\0';

    char *buffer = (char *)malloc(BUFSIZE);
    str[0] = '\0';

    while (fgets(buffer, BUFSIZE, fp) != NULL)
    {
        strcat(str, buffer);
    }

    free(buffer);

    fclose(fp);

    return str;
}

void zip(char *buffer)
{
    for (size_t i = 0; i < strlen(buffer); i++)
    {
        char ch = buffer[i];
        int count = 1;
        while (ch == buffer[i + 1])
        {
            count++;
            i++;
        }

        fwrite(&count, sizeof(char), 4, stdout);
        fwrite(&ch, sizeof(char), 1, stdout);
    }
}