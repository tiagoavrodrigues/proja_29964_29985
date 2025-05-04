#ifndef MENU_H
#define MENU_H
#include "user.h"

void drawLoginUsername();
void drawLoginPassword(char username[]);
short loginForm(USERLIST userList, USER *loggedUser);
void registerUserInfoForm();

#endif