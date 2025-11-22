#ifndef SORT_H
#define SORT_H

#include "display.h"

#define BESTAVERAGES 10
#define BESTCOURSEAVERAGES 3

Student* bestAverages(Class* class, int* size, int max);
Student* bestCourseAverages(Class* class, char* coursename, int* size, int max);

#endif