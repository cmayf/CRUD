#ifndef USER_H_
#define USER_H_

#include "catalog.h"

struct User
{
    char* username;
    char* option;
    struct Catalog user_catalog;
};

/* Allocation/Deallocation Functions */
struct User* create_user();
void free_user(struct User* user);

#endif