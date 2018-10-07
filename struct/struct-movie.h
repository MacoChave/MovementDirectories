#ifndef PARAMETERS_H_INCLUDED
#define PARAMETERS_H_INCLUDED

#include <string.h>
#include <stdlib.h>

typedef struct Movie Movie;

struct Movie
{
    char genre[20];
    char year[4];
};

Movie newMovie ()
{
    Movie movie;
    memset(movie.genre, '\0', 20);
    memset(movie.year, '\0', 5);

    return movie;
}

#endif // PARAMETERS_H_INCLUDED