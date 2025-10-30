#ifndef COURSES_H
#define COURSES_H

#include "grades.h"

/**
    \struct Course
    \brief Structure contenant le nom, le coefficient et la moyenne d'une matière, ainsi que les notes d'un étudiant dans cette dernière
*/
typedef struct {
    char *name;
    int sizename;
    float coefficient;
    float average;
    Grades grades;
}Course;

Course buildCourse();
Course* destroyCourse(Course* course);

#endif