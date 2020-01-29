#ifndef MOVIE_H_
#define MOVIE_H_

typedef struct Movie
{
    char* title;       
    char* genre;        
    char* year;         
    char* length;
    char* media_type;
    char* date_acquired;
    int review;
    int isMovie;
} Movie;

/* Allocation/Deallocation Functions */
struct Movie* create_movie();
void free_movie(struct Movie* movie);

#endif