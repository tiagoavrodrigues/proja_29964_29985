#include <stdio.h>
#include <locale.h>

#include "include/utils.h"
#include "include/course.h"
#include "include/text.h"
int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");

    clearScreen();
    AREALIST areaList = createAreaList();
    UNITLIST unitList = createUnitList();
    HCOURSELIST hcourseList = createHCourseList(areaList.items, unitList.items);
    if(hcourseList.items == NULL){
        printf("\nOut of memory!\n");
        return -1;
    }

    listAreas(&areaList);
    listUnits(&unitList);
    listHCourses(&hcourseList);
    free(hcourseList.items);
    return 0;
}