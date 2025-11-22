#ifndef STUDENT_API_H
#define STUDENT_API_H

#include "sort.h"

#define SIZE_TOP1 10
#define SIZE_TOP2 3

#define CLASS_DATA void

CLASS_DATA* API_load_students(char* filePath);
int API_save_to_binary_file(CLASS_DATA* pClass, char* filePath);
CLASS_DATA* API_restore_from_binary_file(char* filePath);
void API_display(CLASS_DATA* pClass);
void API_unload(CLASS_DATA* pClass);
char** Best_students(Student* array, int size);
char** API_get_best_students(CLASS_DATA* pClass);
char** API_get_best_students_in_course(CLASS_DATA* pClass, char* course);

#endif