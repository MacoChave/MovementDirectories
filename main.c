#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "interpreter/compiler.h"

char * readLine ()
{
    char * line = (char *)malloc(sizeof(char) * 200);
    char * linep = line;
    size_t lenmax = 200, len = lenmax;

    int c;

    if (line == NULL)
        return NULL;
    
    while(1){
        c = fgetc(stdin);
        if (c == EOF)
            break;
        
        if (--len == 0)
        {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if (linen == NULL)
            {
                free(linep);
                return NULL;
            }

            line = line + (line - linep);
            line = linen;
        }

        if ((*line++ = c) == '\n')
            break;            
    }

    *line = '\0';
    return linep;
}

int main (int argc, char const *argv[])
{
    char string[200];
    int exit = 0;

    do
    {
        printf("\n*******************************\n");
        memset(string, 0, 200);
        strcpy(string, readLine());

        if (strlen(string) > 0 && isalpha(string[0]))
        {
            if (strncmp(string, "exit", sizeof(char) * 4) == 0)
                break;
            analizeLine(string);
        }
        else
            break;

        printf("\n*******************************\n");
    } while (!exit);
    
    return 0;
}