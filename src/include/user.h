#ifndef USER_H
#define USER_H

#define USERNAME_MAX_CHAR 21
#define PASSWORD_MAX_CHAR 21

#define USER_FILENAME "data/user.dat"

typedef struct user{
    enum { Admin, Applicant } type;
    unsigned char username[USERNAME_MAX_CHAR];
    unsigned char password[PASSWORD_MAX_CHAR];
} USER;

typedef struct userlist{
    unsigned short count;
    USER *users;
} USERLIST;

USERLIST createUserList();
short authenticateUser(USERLIST userList, USER user);
short addUser(USERLIST *userList, USER newUser);
short userExists(USERLIST userList, char username[USERNAME_MAX_CHAR]);
short saveUserData(USERLIST userList);
short loadUserData(USERLIST *userList);

#endif