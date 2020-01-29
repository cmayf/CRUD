#ifndef LOG_H_
#define LOG_H_

#include "user.h"

void add_user_log(struct User* u);
void open_user_log(struct User* u);
void add_user(struct User* u); 
void open_user(struct User* u);


#endif