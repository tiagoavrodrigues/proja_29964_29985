#include <stdio.h>
#include <string.h>
#include "include/menu.h"
#include "include/utils.h"
#include "include/user.h"

void drawLoginUsername(){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|             LOGIN MENU               |\n"
        "+--------------------------------------+\n"
        "| USERNAME: "
    );
}

void drawLoginPassword(char username[]){
    printf("\n");
    printf(
        "+--------------------------------------+\n"
        "|             LOGIN MENU               |\n"
        "+--------------------------------------+\n"
        "| USERNAME: %s\n"
        "| PASSWORD: ",
        username
    );
}

short login(USERLIST userList, USER *loggedUser){
    char username[USERNAME_MAX_CHAR];
    char password[PASSWORD_MAX_CHAR];

    clearScreen();
    drawLoginUsername();

    fgets(username, USERNAME_MAX_CHAR, stdin);
    username[strcspn(username, "\n")] = '\0';
    if(!userExists(userList, username)){

    }

    short result;
    do{
        clearScreen();
        drawLoginPassword(username);
        inputPasswordMask(password);

        USER tempUser = {Applicant};

        strcpy(tempUser.username, username);
        strcpy(tempUser.password, password);
        
        result = authenticateUser(userList, tempUser);

        switch(result){
            case 0: printf("\n > "); printColored("Password inválida! ", Red, 0); _pause(); break;
            case 1: *loggedUser = (USER) { Admin, username, password }; break;
            case 2: *loggedUser = (USER) { Applicant, username, password }; break;
            default: printf("\n > "); printColored("Ocorreu um erro! ", Red, 0); _pause(); break;
        }
    }while(result < 1);

    return 0;
}