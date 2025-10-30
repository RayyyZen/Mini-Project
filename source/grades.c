#include "grades.h"

Grades constructeurGrades(){
    Grades grades;
    grades.taille=0;
    grades.capacite=0;
    grades.valeurs=NULL;
    return grades;
}

void destructeurGrades(Grades *grades){
    grades->taille=0;
    grades->capacite=0;
    free(grades->valeurs);
    grades->valeurs=NULL;
    //free(grades);
    //grades=NULL;
    //Car dans la structure Course j'y ai mis comme attribut un Grades grades et non pas un Grades *grades
}