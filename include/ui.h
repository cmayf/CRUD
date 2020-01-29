#ifndef UI_H_
#define UI_H_

#include "log.h"
#include "user.h"
#include "catalog.h"

void username(struct User* u);
void user_catalog(struct User* u);
void options(struct User* u);
void title(struct User* u);
void user_interface();

#endif