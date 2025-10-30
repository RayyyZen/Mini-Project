#ifndef GRADES_H
#define GRADES_H

#include "library.h"

/**
    \struct Grades
    \brief Structure contenant plusieurs notes d'un étudiant dans une matière
*/
typedef struct {
    int size;
    int capacity;//Sert à reallouer le tableau de valeurs si besoin
    float *values;
}Grades;

Grades buildGrades();
void destroyGrades(Grades* grades);

#endif