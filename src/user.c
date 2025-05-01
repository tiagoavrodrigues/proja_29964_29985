#include <stdio.h>
#include <stdlib.h>
#include "include/user.h"

USERLIST createUserList(){
    USER *users = (USER *) calloc(1, sizeof(USER));

    users[0] = (USER) { Admin, "admin", "admin" };
    
    return (USERLIST) { 1, (USER *) users };
}

short registerNewUser(USERLIST *userList, USER newUser){
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

short saveUserData(USERLIST *userList){
    FILE *fp;

    if((fp = fopen(USER_FILENAME, "rb")) == NULL){
        return -1;
    };

    fwrite(&userList->count, sizeof(unsigned short), 1, fp);
    fwrite(userList->users, sizeof(USER), userList->count, fp);

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