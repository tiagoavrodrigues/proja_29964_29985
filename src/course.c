#include <stdio.h>
#include <string.h>
#include "include/course.h"
#include "include/org.h"
#include "include/utils.h"

#define AREA_ITEM_QUANTITY 22
#define HCOURSE_ITEM_QUANTITY 26

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

AREA* getArea(AREA *areas, unsigned short id){
    if(areas == NULL || id >= AREA_ITEM_QUANTITY) return NULL;

    return &areas[id];
}

void listAreas(AREALIST *areaList){
    if(areaList == NULL || !areaList->count || areaList->items == NULL){
        return;
    }
    printf(
        "+-----+--------------------------------------------+\n"
        "| ID  | Area Description                           |\n"
        "+-----+--------------------------------------------+\n"
    );
    for (unsigned short i = 0; i < areaList->count; i++) {
        printf(
            "| % 3d | ",
            areaList->items[i].id,
            areaList->items[i].description
        );
        printFixedWidth(areaList->items[i].description, ' ', 42);
        printf("|\n");
    }
    printf("+-----+--------------------------------------------+\n");
}

HCOURSELIST createHCourseList(AREA *areas, UNIT *units) {
    HCOURSE *hcourses = (HCOURSE *) calloc(HCOURSE_ITEM_QUANTITY, sizeof(HCOURSE));

    if(hcourses == NULL) return (HCOURSELIST) {HCOURSE_ITEM_QUANTITY, (HCOURSE *) NULL};

    int i = 0;
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP001", "Gestão Hoteleira", *getArea(areas, 4), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP002", "Construção e Reabilitação", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP003", "Desenvolvimento Web e Multimédia", *getArea(areas, 9), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP004", "Impressão 3D e Maquinação Automática", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP005", "Manutenção Mecânica", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP006", "Mecatrónica", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP007", "Sistemas Elétricos de Energia", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP008", "Sistemas Eletrónicos e Computadores", *getArea(areas, 10), *getUnit(units, 0), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP009", "Tecnologias e Programação de Sistemas de Informação", *getArea(areas, 9), *getUnit(units, 0), Open };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP010", "Terapias Termais e Bem-Estar", *getArea(areas, 15), *getUnit(units, 1), Open };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP011", "Arte e Fabricação Digital", *getArea(areas, 0), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP012", "Artes e Tecnologia [Luz, Som e Imagem]", *getArea(areas, 0), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP013", "Ilustração e Produção Gráfica", *getArea(areas, 0), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP014", "Intervenção Educativa em Creche", *getArea(areas, 1), *getUnit(units, 2), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP015", "Intervenção Sociocomunitária e Envelhecimento", *getArea(areas, 21), *getUnit(units, 2), Closed };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP016", "Treino Desportivo", *getArea(areas, 15), *getUnit(units, 3), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP017", "Trabalhos em Altura e Acesso por Cordas", *getArea(areas, 10), *getUnit(units, 3), Open };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP018", "Cuidados Veterinários", *getArea(areas, 14), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP019", "Fruticultura, Viticultura e Enologia", *getArea(areas, 13), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP020", "Gestão de Empresas Agrícolas", *getArea(areas, 13), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP021", "Indústrias Biotecnológicas", *getArea(areas, 6), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP022", "Riscos e Proteção Civil", *getArea(areas, 20), *getUnit(units, 4), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP023", "Turismo Rural e de Natureza", *getArea(areas, 4), *getUnit(units, 4), Open };

    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP024", "Contabilidade e Gestão para PME", *getArea(areas, 4), *getUnit(units, 5), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP025", "Marketing Digital e E-Commerce", *getArea(areas, 4), *getUnit(units, 5), Open };
    hcourses[i++] = (HCOURSE) { CTeSP, "CTESP026", "Transportes e Logística", *getArea(areas, 4), *getUnit(units, 5), Open };

    return (HCOURSELIST) {HCOURSE_ITEM_QUANTITY, (HCOURSE *) hcourses};
}


COURSE* getHCourse(HCOURSELIST *hcourseList, unsigned char code[]){
    if(hcourseList == NULL || !hcourseList->count || code == NULL || code[0] == '\0'){
        return NULL;
    }

    for(unsigned short i = 0; i < hcourseList->count; i++){
        if(strcmp(hcourseList->items->code, code) == 0) return &(hcourseList->items[i]); 
    }

    return NULL;
}

void listHCourses(HCOURSELIST *hcourseList){
    if (hcourseList == NULL || !hcourseList->count || hcourseList->items == NULL) {
        return;
    }

    printf(
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
        "| Code      | Course Description                              | Area                                | School | State  |\n"
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
    );
    for (unsigned short i = 0; i < hcourseList->count; i++) {
        printf(
            "| %-9s | ",
            hcourseList->items[i].code
        );
        printFixedWidth(hcourseList->items[i].description, ' ', 46); 
        printf(" | ");
        printFixedWidth(hcourseList->items[i].area.description, ' ', 34); 
        printf(" | %-6s | %-6s |\n",
            hcourseList->items[i].school.acronym,
            hcourseList->items[i].state == Open ? "Open" : "Closed"
        );
    }
    printf("+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n");
}

void listHCoursesAsc(HCOURSELIST *hcourseList){

}

void listHCoursesByUnit(HCOURSELIST *hcourseList, unsigned short unitID){
    if (hcourseList == NULL || !hcourseList->count || hcourseList->items == NULL) {
        return;
    }

    printf(
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
        "| Code      | Course Description                              | Area                                | School | State  |\n"
        "+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n"
    );
    
    for (unsigned short i = 0; i < hcourseList->count; i++) {
        if(hcourseList->items[i].school.id == unitID){
            printf(
                "| %-9s | ",
                hcourseList->items[i].code
            );
            printFixedWidth(hcourseList->items[i].description, ' ', 46); 
            printf(" | ");
            printFixedWidth(hcourseList->items[i].area.description, ' ', 34); 
            printf(" | %-6s | %-6s |\n",
                hcourseList->items[i].school.acronym,
                hcourseList->items[i].state == Open ? "Open" : "Closed"
            );
        }
    }
    printf("+-----------+-------------------------------------------------+-------------------------------------+--------+--------+\n");
}

void setHCourseState(HCOURSE *course, eState newState){
    if (course == NULL) {
        return;
    }

    course->state = newState;
}