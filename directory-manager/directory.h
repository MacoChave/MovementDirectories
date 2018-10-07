#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

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

int createFolder (char * directory)
{
    return mkdir(directory, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
}

int moveFile (char * filename, char * destiny)
{
    return rename(filename, destiny);
}

void orderFile (char * rootDirectory, char * filename)
{
    FILE * file;
    Movie movie = newMovie();

    if ((file = fopen(filename, "r")) == NULL)
    {
        perror("[e]\n");
        return;
    }

    fgets(movie.year, 5, file); // OBTENER AÑO
    fgets(movie.genre, 20, file); // OBTENER EL SALTO DE LÍNEA
    fgets(movie.genre, 20, file); // OBTENER GENERO
    fflush(file);
    fclose(file);

    char * newDirectory = (char *)malloc(sizeof(char) * 120);
    memset(newDirectory, '\0', 120);
    
    strcpy(newDirectory, movie.genre);
    strcat(newDirectory, "/"); // PARA ASEGURAR CARPETA GENERO
    if (!createFolder(newDirectory))
    {
        strcat(newDirectory, movie.year);
        strcat(newDirectory, "/"); // PARA ASEGURAR CARPETA AÑO
        (!createFolder(newDirectory)) ? printf("Directorio creado\n") : perror("[e]\n");
    }

    strcat(newDirectory, filename);
    (!moveFile(filename, newDirectory)) ? printf("Archivo movido\n") : perror("[e]\n");
        
    free(newDirectory);
    newDirectory = NULL;
}

int orderLibrary (char * rootDirectory)
{
    DIR * dir;
    struct dirent * stdirent;

    dir = opendir(rootDirectory);
    if (dir == NULL)
    {
        perror("[e]\n");
        return 0;
    }

    int i = 1;
    while ((stdirent = readdir(dir)) != NULL)
    {
        printf("FILE: %s\n", stdirent->d_name);
        if (!isFile(stdirent->d_name))
            continue; // NO ES UN ARCHIVO PELICULA
        
        orderFile(rootDirectory, stdirent->d_name); // ORDENAR ARCHIVO PELICULA
        i++;
    }
    printf(">> Se ordenaron los ficheros\n");
    
    closedir(dir);
    return 1;
}

#endif // MANAGER_H_INCLUDED