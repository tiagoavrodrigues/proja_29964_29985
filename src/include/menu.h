#ifndef MENU_H
#define MENU_H
#include "user.h"
#include "course.h"
#include "applicant.h"
#include "application.h"
#include "course.h"

typedef enum formtype{ Confirmation, Information } eFormType;
typedef enum registrationtype{ Registration, Update } eRegistrationType;


void drawLoginUsername();
void drawLoginPassword(char username[]);
void drawNewPassword(char username[]);
short loginForm(USERLIST *userList, USER *loggedUser, AREALIST areaList, HCOURSELIST hcourseList, APPLICANT *currentApplicant, APPLICANTLIST *applicantList, ELEM **listHeader);
void registerUserInfoForm(AREALIST areaList, APPLICANT *newApplicant, HCOURSELIST hcourseList, eRegistrationType registrationType);
void printFilledForm(APPLICANT newApplicant, HCOURSELIST hcourseList, eFormType formType);
void drawUserMenu(APPLICANT currentApplicant, eState applicationsState);
void drawAdminMenu(eState *applicationsState);
#endif