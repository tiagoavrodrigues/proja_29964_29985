#include <stdio.h>
#include "include/course.h"

#define AREA_ITEM_QUANTITY 22

AREALIST createAreaList(){

    static const AREA items[AREA_ITEM_QUANTITY] = {
        { 0, "Artes" },
        { 1, "Humanidades" },
        { 2, "Ciências Sociais e do Comportamento" },
        { 3, "Informação e Jornalismo" },
        { 4, "Ciências Empresariais" },
        { 5, "Direito" },
        { 6, "Ciências da Vida" },
        { 7, "Ciências Físicas" },
        { 8, "Matemática e Estatística" },
        { 9, "Informática" },
        { 10, "Engenharia e Técnicas Afins" },
        { 11, "Indústrias Transformadoras" },
        { 12, "Arquitetura e Construção" },
        { 13, "Agricultura, Silvicultura e Pescas" },
        { 14, "Ciências Veterinárias" },
        { 15, "Saúde" },
        { 16, "Serviços Sociais" },
        { 17, "Serviços Pessoais" },
        { 18, "Serviços de Transporte" },
        { 19, "Proteção do Ambiente" },
        { 20, "Serviços de Segurança" },
        { 21, "Desconhecido ou não especificado" }
    };

    return (AREALIST) {AREA_ITEM_QUANTITY, (AREA *)items};
}

void listAreas(AREALIST *areaList){
    if(!areaList->count || !areaList->items){
        return;
    }
    printf(
        "+-----+--------------------------------------------+\n"
        "| ID  | Area Description                            \n"
        "+-----+--------------------------------------------+\n"
    );
    for (unsigned short i = 0; i < areaList->count; i++) {
        printf(
            "| % 3d | %-42.42s \n",
            areaList->items[i].id,
            areaList->items[i].description
        );
    }
    printf("+-----+--------------------------------------------+\n");
    return;
}
