#ifndef STUDENTS_H
#define STUDENTS_H

#include "courses.h"

typedef enum{
    MATHS = 0,
    FRANCAIS,
    HISTOIRE,
    GEOGRAPHIE,
    CHIMIE,
    PHYSIQUE,
    INFORMATIQUE,
    BIOLOGIE,
    ANGLAIS,
    EPS,
    PHILOSOPHIE,
    ECONOMIE,
    SOCIOLOGIE,
    ARTS,
    MUSIQUE,
    TECHNOLOGIE,
    LATIN,
    ESPAGNOL,
    ALLEMAND,
    SOCIALES
}CourseIndex;

#define NBMATIERES 20
#define SCIENCES_MASK ((1<<MATHS)|(1<<CHIMIE)|(1<<PHYSIQUE)|(1<<INFORMATIQUE)|(1<<BIOLOGIE)|(1<<TECHNOLOGIE))
#define HUMANITIES_MASK ((1<<FRANCAIS)|(1<<HISTOIRE)|(1<<GEOGRAPHIE)|(1<<ANGLAIS)|(1<<EPS)|(1<<PHILOSOPHIE)|(1<<ECONOMIE)|(1<<SOCIOLOGIE)|(1<<ARTS)|(1<<MUSIQUE)|(1<<LATIN)|(1<<ESPAGNOL)|(1<<ALLEMAND)|(1<<SOCIALES))
#define YEAR_MASK (SCIENCES_MASK | HUMANITIES_MASK)

/**
    \struct Student
    \brief Structure contenant les informations clées d'un étudiant de la promotion
*/
typedef struct {
    int id;
    int age;
    char *fname;//first name
    char *lname;//last name
    int sizefname;
    int sizelname;
    int size;
    int capacity;//Sert à reallouer le tableau de matières si besoin
    Course *courses;
    float average;
    uint64_t index;//Variable à 64 bits qui stocke la validation de l'étudiant dans chacune des matières
}Student;

Student buildStudent();
Student* destroyStudent(Student* student);
int compareMask(Student* student, uint64_t mask);

#endif