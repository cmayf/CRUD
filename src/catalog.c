#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "catalog.h"


/* Allocate catalog object */
struct Catalog* create_catalog()
{
    struct Catalog *retVal = malloc(sizeof(struct Catalog) * 2);
    retVal->size = 0;
    retVal->movies = malloc(sizeof(struct Movie*)*1000);
    for(int i = 0; i < (retVal->size + 1); ++i)
        retVal->movies[i] = *create_movie();
    return retVal;
}


/* Deallocate catalog object */
void free_catalog(struct Catalog* catalog)
{
    for(int i = 0; i < (catalog->size); ++i)
        free_movie(&catalog->movies[i]);
    free(catalog->movies);
    free(catalog);
}


/* Utility Functions */

/* Check if movie already exists in catalog */
int check_catalog(struct Catalog* user_catalog, char* title)
{
    char* inputTitle = lowercase(title);
    for(int i = 0; i < user_catalog->size; i++)
    {
        char* movieTitle = lowercase(user_catalog->movies[i].title);
        if(strcmp(inputTitle, movieTitle) == 0)
        {
            free(inputTitle);
            free(movieTitle);
            return i;
        }
        free(movieTitle);
    }
    free(inputTitle);
    return -1;
}

/* Print catalog */
void print_catalog(struct Catalog user_catalog)
{
    for(int i = 0; i < user_catalog.size; ++i)
    {
        printf("%s\n", user_catalog.movies[i].title);
    }
}

// Detects when the user presses enter
void detect_enter()
{
    printf("Press [Enter] to continue.\n\n");
    while(getchar() != '\n');
}

//Checks if user input is 'y' or not
int prompt_yes_no()
{
    while(1)
    {
        if(getchar() == 'y' || getchar() == 'Y')
        {
            printf("\n\n");
            getchar();
            return 1;
        }
        else return 0;
    }
}

/*---------------- CRUD Functions ------------------*/

/* If a title is not found but possible matches are the user is
   asked whether or not they would like to add one of the matches */
void add_match(struct Catalog* user_catalog)
{
    printf("Did you mean one of these titles:\n");
    printf("---------------------------------------------\n");
    for(int i = 0; i < possibleMatchIndex; ++i)
        printf("[%d]: %s\n", i, possibleMatches[i]);
    printf("---------------------------------------------\n");

    char* userInput = malloc(sizeof(char*));
    printf("Enter the number corresponding to the movie\n");
    printf("you wish to add or \"no\" to exit to menu.\n");
    printf("---------------------------------------------\n");

    printf("Add movie: ");
    scanf("%3[^\n]", userInput);
    scanf("%*[^\n]");
    (void) getchar();
    if(strcmp(userInput, "no") == 0)
    {
        free(userInput);
        freePossibleMatches();
        return;
    }
    else if(strcmp(userInput, "0") == 0 || strcmp(userInput, "1") == 0 || strcmp(userInput, "2") == 0 ||
            strcmp(userInput, "3") == 0 || strcmp(userInput, "4") == 0 || strcmp(userInput, "5") == 0 ||
            strcmp(userInput, "6") == 0 || strcmp(userInput, "7") == 0 || strcmp(userInput, "8") == 0 ||
            strcmp(userInput, "9") == 0 || strcmp(userInput, "10") == 0)
    {
        printf("\nAdding: \"%s\" to your catalog.\n\n\n\n", possibleMatches[atoi(userInput)]);
        create(user_catalog, possibleMatches[atoi(userInput)]);
        free(userInput);
        freePossibleMatches();
        return;
    }
    else
    {
        printf("Invalid option. Try again.\n");
        free(userInput);
        add_match(user_catalog);
    }
}

/* Searches for movie in database and adds it to catalog if found.*/
void create(struct Catalog* user_catalog, char* title)
{
    struct Movie* new_movie = create_movie();
    new_movie = search_data(title);
    if(check_catalog(user_catalog, title) != -1)
    {
        printf("Movie already exists in catalog.\n\n");
        return;
    }
    if(new_movie == Movie_Nil)
    {
        printf("Movie not found. Can you be more specific?\n\n");
        if(possibleMatchIndex > 1)
            add_match(user_catalog);
        return;
    }
    strcpy(new_movie->media_type, "(blank)");
    strcpy(new_movie->date_acquired, "(blank)");
    new_movie->review = 0;
    user_catalog->movies[user_catalog->size] = *new_movie;
    ++user_catalog->size;
}

/* Rentry of create function to add movie from log */
void create_l(struct Catalog* user_catalog, char* title, char* mt, char* da, char* rv)
{
    struct Movie* new_movie = create_movie();
    new_movie = search_data(title);
    if(check_catalog(user_catalog, title) != -1)
    {
        printf("Movie already exists in catalog.\n\n");
        return;
    }
    if(new_movie == Movie_Nil)
    {
        printf("Movie not found.\n\n");
        if(possibleMatchIndex > 1)
            add_match(user_catalog);
        return;
    }
    strcpy(new_movie->media_type, mt);
    strcpy(new_movie->date_acquired, da);
    new_movie->review = atoi(rv);
    user_catalog->movies[user_catalog->size] = *new_movie;
    ++user_catalog->size;
}

void printMovieDetails(struct Catalog* user_catalog, char* title)
{
    int movie_index = check_catalog(user_catalog, title);
    if(movie_index == -1)
    {
        printf("Movie not found. Enter the movie as it appears in your catalog.\n\n");
        return;
    }

    printf("\n\n---------------------------\n");
    printf("Title: %s\n", title);
    printf("---------------------------\n");
    printf("Year: %s\n", user_catalog->movies[movie_index].year);
    printf("Genre: %s\n", user_catalog->movies[movie_index].genre);
    printf("Length: %s mins\n", user_catalog->movies[movie_index].length);
    printf("Media Type: %s\n", user_catalog->movies[movie_index].media_type);
    printf("Date Acquired: %s\n", user_catalog->movies[movie_index].date_acquired);
    if(user_catalog->movies[movie_index].review > 0 && user_catalog->movies[movie_index].review < 11)
        printf("Review: %d/10\n", user_catalog->movies[movie_index].review);
    else printf("Review: (blank)\n");
    printf("---------------------------\n\n");
}

/* Provides details about a movie in the user's catalog */
void read(struct Catalog* user_catalog, char* title)
{
    printMovieDetails(user_catalog, title);
    detect_enter();
}

/* Checks if a user's update input is valid */
int isValidUpdateInput(char* option, char* input)
{
    input = lowercase(input);
    if(strcmp(option, "da") == 0)
    {
        if(input[2] != '/' || input[5] != '/' || strlen(input) != 10)
        {
            printf("Invalid input. Please use the specified date format.\n\n");
            return 0;
        }
        else return 1;
    }
    else if(strcmp(option, "mt") == 0)
    {
        if(strcmp(input, "dvd") != 0 && strcmp(input, "blu-ray") != 0 && strcmp(input, "digital") != 0 && strcmp(input, "film") != 0)
        {
            printf("Invalid input. Select a valid media type.\n\n");
            return 0;
        }
        else return 1;
    }
    else if(strcmp(option, "rv") == 0)
    {
        if(atoi(input) < 0 || atoi(input) > 10)
        {
            printf("Invalid input. Enter a number between [1-10].\n\n");
            return 0;
        }
        else return 1;
    }
    return 0;
}

/* Update's user provided movie details */
void update(struct Catalog* user_catalog, char* title)
{

    char* option = malloc(sizeof(char*));
    char* input = malloc(sizeof(char*));

    int movie_index = check_catalog(user_catalog, title);
    if(movie_index == -1)
    {
        printf("Movie not found.\n\n");
        free(option);
        return;
    }

    printMovieDetails(user_catalog, title);
    printf("| Update Media Type (mt) | Update Date Acquired (da) | Update Review (rv) | : ");
    scanf("%3[^\n]", option);
    scanf("%*[^\n]");
    (void) getchar();
    printf("\n");


    if(strcmp(option, "mt") == 0)
    {
        printf("Media Type (DVD, Blu-ray, Digital, or Film) : ");
        scanf("%20s", input);
        scanf("%*[^\n]");
        (void) getchar();
        if(isValidUpdateInput(option, input) == 1) {
            strcpy(user_catalog->movies[movie_index].media_type, input);
            printMovieDetails(user_catalog, title);
        }
    }
    else if(strcmp(option, "da") == 0)
    {
        printf("Date Acquired (MM/DD/YYYY) : ");
        scanf("%20s", input);
        scanf("%*[^\n]");
        (void) getchar();
        if(isValidUpdateInput(option, input) == 1) {
            strcpy(user_catalog->movies[movie_index].date_acquired, input);
            printMovieDetails(user_catalog, title);
        }
    }
    else if(strcmp(option, "rv") == 0)
    {
        printf("Review ([1-10]/10) : ");
        scanf("%20s", input);
        scanf("%*[^\n]");
        (void) getchar();
        if(isValidUpdateInput(option, input) == 1) {
            user_catalog->movies[movie_index].review = atoi(input);
            printMovieDetails(user_catalog, title);
        }
    }
    else
        printf("Invalid option. ");

    free(option);
    free(input);
    printf("Do you wish to continue updating (y/n) : ");
    if(prompt_yes_no() == 1)
        update(user_catalog, title);
    printf("\n\n\n");
    return;
}


/* Delete's movie from the user's catalog */
void delete(struct Catalog* user_catalog, char* title)
{
    int movie_index = check_catalog(user_catalog, title);
    if(movie_index == -1)
    {
        printf("Movie not found.\n\n");
        return;
    }

    for(int i = movie_index; i < user_catalog->size; i++)
    {

        user_catalog->movies[i] = user_catalog->movies[i+1];
    }
    --user_catalog->size;
}
