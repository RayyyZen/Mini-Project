#ifndef SORT_H
#define SORT_H

#include "display.h"

#define BESTAVERAGES 10
#define BESTCOURSEAVERAGES 3

Student* bestAverages(Class* class, int* size, int max);
Student* bestCourseAverages(Class* class, char* coursename, int* size, int max);
int compareStrings(char *str1, char *str2);
int compareFirstName(Student* student1, Student* student2);
int compareLastName(Student* student1, Student* student2);
int compareAverage(Student* student1, Student* student2);
float getMinimumAverage(Student* std);
int compareMinimum(Student* student1, Student* student2);

#endif