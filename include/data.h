#ifndef DATA_H
#define DATA_H

#include "class.h"

void addStudent(Class* class, char* line);
void addCourse(Student* student, char* line);
void addGrade(Class* class, Student* allcourses, pTree tree, char* line);
void dataStorage(Class* class, char* path);

#endif