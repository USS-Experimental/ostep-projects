#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

void cat(FILE *fp);

int main(int argc, char *argv[])
{
    // Check the command line input, return 0 when no files are specified
    if (argc < 2)
    {
        return 0;
    }
    
    // Read each filename in argv[]
    for (size_t i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        cat(fp); // Read and print every lines in file

        fclose(fp);
    }
    
    return 0;
}

void cat(FILE *fp)
{
    char buffer[BUFSIZE];

    while (fgets(buffer, BUFSIZE, fp) != NULL)
    {
        printf("%s", buffer);
    }
}