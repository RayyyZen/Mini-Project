#ifndef STUDENT_API_H
#define STUDENT_API_H

#define SIZE_TOP1 10
#define SIZE_TOP2 3

#define ALPHA_FIRST_NAME 1
#define ALPHA_LAST_NAME 2
#define AVERAGE 3
#define MINIMUM 4

#define KEYSIZE 16

#define CLASS_DATA void

CLASS_DATA* API_load_students(char* filePath);
int API_save_to_binary_file(CLASS_DATA* pClass, char* filePath);
CLASS_DATA* API_restore_from_binary_file(char* filePath);
void API_display(CLASS_DATA* pClass);
void API_unload(CLASS_DATA* pClass);
char** Best_students(CLASS_DATA* pArray, int size);
char** API_get_best_students(CLASS_DATA* pClass);
char** API_get_best_students_in_course(CLASS_DATA* pClass, char* course);
int API_set_sorting_mode(CLASS_DATA* pClass, int mode);
char** API_sort_students(CLASS_DATA* pClass);
void API_display_results_per_field(CLASS_DATA* pClass);
int API_cipher(char* pIn, char* pOut);
int API_decipher(char* pIn, char* pOut);

#endif