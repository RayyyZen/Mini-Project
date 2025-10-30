#ifndef GRADES_H
#define GRADES_H

#include "library.h"

/**
    \struct Grades
    \brief Structure contenant plusieurs notes d'un étudiant dans une matière
*/
typedef struct {
    int taille;
    int capacite;
    float *valeurs;
}Grades;

Grades constructeurGrades();
void destructeurGrades(Grades *grades);

#endif