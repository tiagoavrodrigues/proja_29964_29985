#ifndef USER_H
#define USER_H

typedef struct{
    enum { Admin, Applicant } type;
    unsigned char username[21];
    unsigned char password[21];
} USER;

#endif