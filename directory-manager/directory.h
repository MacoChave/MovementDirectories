#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "../struct/struct-movie.h"

int isFile (char * filename)
{
    if (strncmp(filename, ".", sizeof(char)) == 0)
        return 0;

    char * cpyPath = (char *)malloc(strlen(filename));
    strcpy(cpyPath, filename);
    char * temp = (char *)malloc(strlen(filename));
    memset(temp, 0, strlen(filename));

    temp = strtok(cpyPath, ".");
    if (strcmp(temp, "README") == 0)
        return 0;
    temp = strtok(NULL, ".");
    if (temp != NULL && strcmp(temp, "txt") == 0)
        return 1;
    
    return 0;
}

int createFolder (char * newDirectory)
{
    size_t size = strlen(newDirectory) + sizeof(char) * 12;
    char * cmd = (char *)malloc(size);
    memset(cmd, 0, size);
    strcpy(cmd, "mkdir -p ");
    strcat(cmd, newDirectory);

    return (system(cmd) == 0) ? 1 : 0;
}

int moveFile (char * oldDirectory, char * newDirectory)
{
    printf("OLD: %s NEW: %s\n", oldDirectory, newDirectory);
    return (rename(oldDirectory, newDirectory) == 0) ? 1 : 0;
}

void orderFile (char * rootDirectory, char * filename)
{
    FILE * file;
    Movie movie = newMovie();

    if ((file = fopen(filename, "r")) == NULL)
    {
        perror("[e] ARCHIVO NO ACCESIBLE\n");
        return;
    }

    fgets(movie.year, 5, file);
    fgets(movie.genre, 20, file);
    fgets(movie.genre, 20, file);
    fflush(file);
    fclose(file);

    char * oldDirectory = (char *)malloc(sizeof(char) * 120);
    char * newDirectory = (char *)malloc(sizeof(char) * 120);
    memset(oldDirectory, '\0', 120);
    memset(newDirectory, '\0', 120);
    
    strcpy(newDirectory, "'");
    strcat(newDirectory, rootDirectory);
    strcat(newDirectory, "/");
    strcat(newDirectory, movie.genre);
    strcat(newDirectory, "/");
    strcat(newDirectory, movie.year);
    strcat(newDirectory, "/");
    strcat(newDirectory, filename);
    strcat(newDirectory, "'");

    strcpy(oldDirectory, "'");
    strcat(oldDirectory, rootDirectory);
    strcat(oldDirectory, "/");
    strcat(oldDirectory, filename);
    strcat(oldDirectory, "'");
    
    createFolder(newDirectory);
    (moveFile(oldDirectory, newDirectory)) ?
        printf("[i] Archivo ordenado\n") : perror("[e] No pudo moverse el archivo\n");
        
    free(newDirectory);
    free(oldDirectory);
    newDirectory = NULL;
    oldDirectory = NULL;
}

int orderLibrary (char * rootDirectory)
{
    DIR * dir;
    struct dirent * stdirent;

    dir = opendir(rootDirectory);
    if (dir == NULL)
    {
        perror("[e] ERROR AL ABRIR DIRECTORIO\n");
        return 0;
    }

    int i = 1;
    while ((stdirent = readdir(dir)) != NULL)
    {
        printf("FILE: %s\n", stdirent->d_name);
        if (!isFile(stdirent->d_name))
            continue;
        
        orderFile(rootDirectory, stdirent->d_name);
        i++;
    }
    printf("[i] SE ORDENARON %d ARCHIVOS", i);
    
    closedir(dir);
    return 1;
}

#endif // MANAGER_H_INCLUDED