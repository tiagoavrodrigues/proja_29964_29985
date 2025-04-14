#ifndef USER_H
#define USER_H

typedef struct{
    enum { Admin, Applicant } type;
    char username[21];
    char password[21];
} USER;

#endif