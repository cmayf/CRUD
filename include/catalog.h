#ifndef CATALOG_H_
#define CATALOG_H_

#include "data.h"
#include "tree.h"

struct Catalog
{
    struct Movie* movies;
    int size;
};

/* Allocation/Deallocation Functions */
struct Catalog* create_catalog();
void free_catalog(struct Catalog* catalog);

/* Utility Functions */
int check_catalog(struct Catalog* user_catalog, char* title);
void print_catalog(struct Catalog user_catalog);
void detect_enter();

/* CRUD Functions */
void create(struct Catalog* user_catalog, char* title);
void create_l(struct Catalog* user_catalog, char* title, char* mt, char* da, char* rv);
void read(struct Catalog* user_catalog, char* title);
void update(struct Catalog* user_catalog, char* title);
void delete(struct Catalog* user_catalog, char* title);

void add_match(struct Catalog* user_catalog);

#endif