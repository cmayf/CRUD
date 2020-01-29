#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "log.h"


/* Creates/updates user.log */
void add_user_log(struct User* u)
{
    char* user_log = malloc(sizeof(u->username) + 4);
    strcpy(user_log, u->username);
    strcat(user_log, ".log");
    FILE* log = fopen(user_log, "w");

    for(int i = 0; i < u->user_catalog.size; i++)
    {
        fprintf(log, "%s", u->user_catalog.movies[i].title);
        fprintf(log, "%s", "\t");
        fprintf(log, "%s", u->user_catalog.movies[i].media_type);
        fprintf(log, "%s", "\t");
        fprintf(log, "%s", u->user_catalog.movies[i].date_acquired);
        fprintf(log, "%s", "\t");
        fprintf(log, "%d", u->user_catalog.movies[i].review);
        fprintf(log, "%c", '\n');
    }
    fclose(log);
    free(user_log);
    return;
}

/* Adds movies from user.log to catalog */
void open_user_log(struct User* u)
{
    char* user_log = malloc(sizeof(u->username) + 4);
    strcpy(user_log, u->username);
    strcat(user_log, ".log");
    FILE* log = fopen(user_log, "r");
    if(log == NULL) printf("Unable to open userlog");

    char line[600];
    int movieIndex = 0, tokenIndex;
    while(fgets(line, 600, log))
    {
        char *title, *mt, *da, *rv;
        char* token = strtok(line, "\t");
        tokenIndex = 1;
        while(token != NULL)
        {
            if(tokenIndex == 1)
            {
                title = malloc(500);
                strcpy(title, token);
            }
            if(tokenIndex == 2)
            {
                mt = malloc(sizeof(char*));
                strcpy(mt, token);
            }
            if(tokenIndex == 3)
            {
                da = malloc(sizeof(char*));
                strcpy(da, token);
            }
            if(tokenIndex == 4)
            {
                rv = malloc(sizeof(char*));
                strcpy(rv, token);
            }
            token = strtok(NULL, "\t\n");
            ++tokenIndex;
        }
        create_l(&u->user_catalog, title, mt, da, rv);
        free(title); free(mt); free(da); free(rv);
        ++movieIndex;
    }
    fclose(log);
    free(user_log);
    return;
}


/* Adds new user */
void add_user(struct User* u)
{
    FILE* user_list = fopen("user_list.txt", "a");
    fputs(u->username, user_list);
    fputs("\n", user_list);
    add_user_log(u);
    fclose(user_list);
    return;
}


/* Opens existing user if username is found in user_list */
void open_user(struct User* u)
{
    FILE* user_list = fopen("user_list.txt", "r");
    if(user_list == NULL)
    {
        add_user(u);
        return;
    }

    while(!feof(user_list))
    {
        char* username = malloc(sizeof(u->username));
        fscanf(user_list, "%s\n", username);
        if(strcmp(username, u->username) == 0)
        {
            open_user_log(u);
            fclose(user_list);
            free(username);
            return;
        }
        free(username);
    }

    fclose(user_list);
    add_user(u);
    return;
}
