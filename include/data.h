#ifndef DATA_H
#define DATA_H

#include "class.h"

int addStudent(Class* class, char* line);
int addCourse(Student* student, char* line);
int addGrade(Class* class, Student* allcourses, pTree tree, char* line);
CourseIndex courseIndex(Course* course);
int dataStorage(Class* class, char* path);
Class* dataDestroy(Class* class);
int cipher(unsigned char* key, int keySize);

#endif