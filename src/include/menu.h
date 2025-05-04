#ifndef MENU_H
#define MENU_H
#include "user.h"

void drawLoginUsername();
void drawLoginPassword(char username[]);
short login(USERLIST userList, USER *loggedUser);

#endif