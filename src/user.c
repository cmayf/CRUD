#include <stdio.h>
#include <stdlib.h>
#include "user.h"

/* Allocate user object */
struct User* create_user()
{
    struct User* retVal = malloc(sizeof (struct User));
    retVal->username = malloc(26);
    retVal->option = malloc(sizeof(char *));
    retVal->user_catalog = *create_catalog();
    return retVal;
}

/* Deallocate user object */
void free_user(struct User* user)
{
    free(user->username);
    free(user->option);
    free_catalog(&user->user_catalog);
    free(user);
}
