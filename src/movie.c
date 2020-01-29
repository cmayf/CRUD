#include <stdio.h>
#include <stdlib.h>
#include "movie.h"

/* Allocate movie object */
struct Movie* create_movie()
{
    struct Movie *retVal = (struct Movie*)malloc(sizeof(struct Movie));
    retVal->title = malloc(sizeof(char*) + 500);
    retVal->genre = malloc(sizeof(char*));
    retVal->year = malloc(sizeof(char*));
    retVal->length = malloc(sizeof(char*));
    retVal->media_type = malloc(sizeof(char*));
    retVal->date_acquired = malloc(sizeof(char*));
    return retVal;
}

/* Deallocate movie object */
void free_movie(struct Movie* movie)
{
    free(movie->title);
    free(movie->genre);
    free(movie->year);
    free(movie->length);
    free(movie->media_type);
    free(movie->date_acquired);
    free(movie);
}
