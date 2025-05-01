#include <stdio.h>
#include "include/org.h"
#include "include/utils.h"

#define UNIT_ELEMENT_QUANTITY 6

UNITLIST createUnitList(){
    static const UNIT units[UNIT_ELEMENT_QUANTITY] = {
        { 0, "ESTG", "Escola Superior de Tecnologia e Gestão" },
        { 1, "ESS", "Escola Superior de Saúde" },
        { 2, "ESE", "Escola Superior de Educação" },
        { 3, "ESDL", "Escola Superior de Desporto e Lazer" },
        { 4, "ESA", "Escola Superior Agrária"},
        { 5, "ESCE", "Escola Superior de Ciências Empresariais"}
    };
    return (UNITLIST) {UNIT_ELEMENT_QUANTITY, (UNIT *) units};
}

UNIT getUnit(UNIT units[] ,unsigned short id){
    if(units == NULL || id >= UNIT_ELEMENT_QUANTITY) return (UNIT) {};

    return units[id];
}

void listUnits(UNITLIST unitList){
    if(unitList.count == 0|| unitList.items == NULL) return;

    printf(
        "+-----+----------+------------------------------------------+\n"
        "| ID  | Acronym  | Designation                              | \n"
        "+-----+----------+------------------------------------------+\n"
    );
    for(unsigned short i = 0; i < unitList.count; i++){
        printf(
            "| %3d | %-8.8s | ",
            unitList.items[i].id,
            unitList.items[i].acronym
        );
        printFixedWidth(unitList.items[i].designation, ' ', 39);
        printf(" |\n");
    }
    printf("+-----+----------+------------------------------------------+\n");
}