#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

/* Database Adapter */

struct Movie* Movie_Nil = NULL;

/* Reads and parses movie data from data.tsv into tree */
void get_data()
{
    FILE* data = fopen("data.tsv", "r");
    if(data == NULL)
        printf("ERROR: Unable to open \"data.tsv\".");

    Root = T_Nil;
    char line[1024];
    while(fgets(line, 1024, data))
    {
        struct Movie* movie = create_movie();
        char* token = malloc(sizeof(char*) + 500);
        int tokenIndex = 1;
        for(token = strtok(line, "\t"); token && *token; token = strtok(NULL, "\t\n"))
        {
             switch(tokenIndex)
            {
                case 1:
                    ++tokenIndex; 
                    break;
                case 2:
                    if(strcmp(token, "movie") == 0) movie->isMovie = 1;
                    else movie->isMovie = 0; 
                    ++tokenIndex;
                    break;
                case 3: 
                    strcpy(movie->title, token);
                    ++tokenIndex;
                    break;
                case 4: 
                    ++tokenIndex;
                    break;
                case 5:
                    ++tokenIndex; 
                    break;
                case 6:
                    strcpy(movie->year, token);
                    ++tokenIndex; 
                    break;
                case 7:  
                    ++tokenIndex; 
                    break;
                case 8: 
                    strcpy(movie->length, token);
                    ++tokenIndex; 
                    break;
                case 9: 
                    strcpy(movie->genre, token);
                    if(movie->isMovie == 1)
                        redBlackInsert(&Root, movie);
                    break;
            }

        }
        free(token);
        //free(movie);
    }
    fclose(data);
}

/* Returns movie from database */
struct Movie* search_data(char* key)
{  
    char* searchKey = lowercase(key);
    Node* node = treeSearch(Root, searchKey);
    if(node != T_Nil)
    {
        free(searchKey);
        return node->movie;
    }
    else
    {
        free(searchKey);
        return Movie_Nil;
    }
}
