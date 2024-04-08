#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

void grep(char *buffer, char *keyword);

int main(int argc, char *argv[])
{
    if (argc < 2) // Check the command line input
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }
    else if (argc == 2) // Only gives search term
    {
        char *keyword = argv[1];
        char buffer[BUFSIZE];
        while (fgets(buffer, BUFSIZE, stdin) != NULL)
        {
            grep(buffer, keyword); // Find the string and print the line
        }
    }
    else // Gives search term and filenames
    {
        for (size_t i = 2; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                printf("wgrep: cannot open file\n");
                exit(EXIT_FAILURE);
            }

            char *keyword = argv[1];
            char *buffer = NULL;
            size_t len = 0;
            while (getline(&buffer, &len, fp) != -1)
            {
                grep(buffer, keyword); // Find the string and print the line
            }

            fclose(fp);
        }
    }

    return 0;
}

void grep(char *buffer, char *keyword)
{
    if (strstr(buffer, keyword) != NULL)
    {
        printf("%s", buffer);
    }
}