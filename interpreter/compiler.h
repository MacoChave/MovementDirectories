#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

#include "../directory-manager/directory.h"

/*
    H | OBTENER AYUDA
    O | ORDENAR BIBLIOTECA
*/
void analizeLine (char * string)
{
    if (strncmp(string, "help", sizeof(char) * 4) == 0)
    {
        printf("[i] help : OBTENER INFORMACIÓN\n");
        printf("[i] order : ORDENAR BIBLIOTECA\n");
        printf("[i] exit : SALIR DE LA APLICACIÓN\n");
    }
    else if (strncmp(string, "order", sizeof(char) * 5) == 0)
    {
        char currentDirectory[120];
        memset(currentDirectory, '\0', 120);
        if (getcwd(currentDirectory, 120) != NULL)
        {
            printf("[i] %s\n", currentDirectory);
            (orderLibrary(currentDirectory)) ? 
                printf("[i] BIBLIOTECA ORDENADA\n") : perror("[e] ERROR AL ORDENAR BIBILOTECA\n");
        }
        else
            perror("[e] NO SE PUEDE OBTENER DIRECTORIO ACUTAL\n");
    }
    else
        perror("[x] OPCIÓN NO RECONOCIDA\n");
}

#endif // COMPILER_H_INCLUDED