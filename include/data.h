#ifndef DATA_H_
#define DATA_H_

#include "tree.h"
#include "movie.h"

extern struct Movie* Movie_Nil;

/* Database Adapter Functions */
void get_data();
struct Movie* search_data(char* key);

#endif