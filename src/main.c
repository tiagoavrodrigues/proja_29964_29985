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
    listAreas(&areaList);
    listUnits(&unitList);
    return 0;
}