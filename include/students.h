#ifndef STUDENTS_H
#define STUDENTS_H

#include "courses.h"

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
}Student;

Student buildStudent();
Student* destroyStudent(Student* student);

#endif