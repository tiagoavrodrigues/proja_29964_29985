#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/user.h"
#include "include/utils.h"

USERLIST createUserList(){
    USER *users = (USER *) calloc(1, sizeof(USER));

    users[0] = (USER) { Admin, "admin", "admin" };
    
    return (USERLIST) { 1, (USER *) users };
}

short addUser(USERLIST *userList, USER newUser){
    if(userList == NULL || !userList->count || userList->users == NULL){
        return -1;
    }

    USER *newUsers = realloc(userList->users, (userList->count + 1) * sizeof(USER));
    if (newUsers == NULL) {
        return -1;
    }

    userList->users = newUsers;
    
    userList->users[userList->count] = newUser;
    userList->count++;

    return 0;
};

short authenticateUser(USERLIST userList, USER user){
    if(userList.count == 0 || user.username == NULL || user.password == NULL) return -1;

    for(unsigned short i = 0; i < userList.count; i++){
        if(strcmp(userList.users[i].username, user.username) == 0
            && strcmp(userList.users[i].password, user.password) == 0) return userList.users[i].type == Admin ? 1 : 2;
    }
    
    return 0;
}

short userExists(USERLIST userList, char username[USERNAME_MAX_CHAR]){
    if(userList.users == NULL || username == NULL || username[0] == '\0') return -1;

    for(unsigned short i = 0; i < userList.count; i++){
        if(strcmp(userList.users[i].username, username) == 0) return 1;
    }

    return 0;
}

short saveUserData(USERLIST userList){
    FILE *fp;

    if((fp = fopen(USER_FILENAME, "wb")) == NULL){
        printColored("\nErro ao abrir o ficheiro " USER_FILENAME "!", Red, 0);
        _pause();
        return -1;
    };

    fwrite(&userList.count, sizeof(unsigned short), 1, fp);
    fwrite(userList.users, sizeof(USER), userList.count, fp);

    fclose(fp);
    return 0;
}

short loadUserData(USERLIST *userList){
    FILE *fp;

    if((fp = fopen(USER_FILENAME, "rb")) == NULL){
        return - 1;
    };

    fread(&userList->count, sizeof(unsigned short), 1, fp);

    userList->users = (USER *) calloc(userList->count, sizeof(USER));

    fread(userList->users, sizeof(USER), userList->count, fp);

    fclose(fp);
    return 0;
}