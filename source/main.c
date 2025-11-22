#include "student_api.h"
#include "sys/time.h"
#include <stdio.h>

long getTimeMilliSec(){
    // Locals
    long result = 0;
    struct timeval tv;
    // Call time + check return
    if(gettimeofday(&tv, NULL) != 0){
        exit(99);
    }
    result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return result;
}



void check_null(){
    CLASS_DATA* p1 = NULL;
    int boolean = 0;

    // check NULL pointers
    p1 = API_load_students(NULL);
    if(p1 != NULL){
        printf("[ERROR] API_load_students(NULL) returns a non-NULL pointer !\n");
        exit(1);
    }
    p1 = API_restore_from_binary_file(NULL);
    if(p1 != NULL){
        printf("[ERROR] API_restore_from_binary_file(NULL) returns a non-NULL pointer !\n");
        exit(1);
    }
    boolean = API_save_to_binary_file(NULL, NULL);
    if(boolean != 0){
        printf("[ERROR] API_save_to_binary_file(NULL, NULL) returns True !\n");
        exit(1);    
    }
    boolean = API_save_to_binary_file(NULL, "test1.dat");
    if(boolean != 0){
        printf("[ERROR] API_save_to_binary_file(NULL, '...') returns True !\n");
        exit(1);    
    }
//    API_display(NULL);
//    API_unload(NULL);

    p1 = API_get_best_students(NULL);
    if(p1 != NULL){
        printf("[ERROR] API_get_best_students(NULL) returns a non-NULL pointer !\n");
        exit(1);
    }
    p1 = API_get_best_students_in_course(NULL, NULL);
    if(p1 != NULL){
        printf("[ERROR] API_get_best_students_in_course(NULL, NULL) returns a non-NULL pointer !\n");
        exit(1);
    }

}

void displayTime(long start, long end){
    long diff = end - start;
    if (diff < 1000){
        printf("  Elapsed time = %ldms \n", diff);
    }
    else if(diff < 60000){
        printf("  Elapsed time = %.3fsec \n", diff/1000.0);        
    }
    else{
        printf("  Elapsed time = %.3fmin \n", diff/60000.0);            
    }
    printf("\n");
}

int main(){

    long start, end;
    int  result;
    
    char** best10 = NULL;
    char** best3  = NULL;
    
    CLASS_DATA* p1 = NULL;
    CLASS_DATA* p2 = NULL;

    // Check null
    printf("==================================\n");
    printf("Checking NULL parameters...\n");
    check_null();    
    printf("\n");
    
    // Load
    printf("==================================\n");
    printf("API_load_students()...\n");
    start = getTimeMilliSec();
    p1 = API_load_students("Data/data.txt");    
    if(p1 == NULL){
        printf("  [ERROR] while trying to load data !\n");        
    }
    end = getTimeMilliSec();
    displayTime(start, end);

    // display Data for both
    printf("==================================\n");
    printf("API_display(p1)...\n");
//    API_display(p1);
    printf("\n");

//*    
    // Save to binary
    printf("==================================\n");
    printf("API_save_to_binary_file()...\n");
    start = getTimeMilliSec();
    result = API_save_to_binary_file(p1, "saved_data.bin");
    end = getTimeMilliSec();
    if(result == 0){
        printf("  [ERROR] while trying to save data !\n");
    }
    displayTime(start, end);
//*/

    // Restore from Binary
    printf("==================================\n");
    printf("API_restore_to_binary_file()...\n");
    start = getTimeMilliSec();
    p2 = API_restore_from_binary_file("saved_data.bin");
    if(p2 == NULL){
        printf("  [ERROR] while trying to restore data !\n");        
    }
    end = getTimeMilliSec();
    displayTime(start, end);

    printf("==================================\n");
    printf("API_display(p2)...\n");
//    API_display(p2);
    printf("\n");
//*    
    // Get best students
    printf("==================================\n");
    printf("API_get_best_students()...\n");
    start = getTimeMilliSec();
    best10 = API_get_best_students(p1);
    end = getTimeMilliSec();
    if(best10 == NULL){
        printf("  [ERROR] while trying to get best students !\n");        
    }
    for(int i=0;i<SIZE_TOP1; i++){
        if(best10[i] == NULL){
            printf("   [ERROR] string pointer is NULL (i=%d) !\n", i);
        }
        else{
            printf("   [%2d] - %s\n", i+1, best10[i]);
        }
    }
    displayTime(start, end);
    
    
    printf("==================================\n");
    printf("API_get_best_students_in_course()...\n");
    start = getTimeMilliSec();
    best3 = API_get_best_students_in_course(p1, "Informatique");
    end = getTimeMilliSec();
    if(best3 == NULL){
        printf("  [ERROR] while trying to get best students in course !\n");        
    }
    for(int i=0;i<SIZE_TOP2; i++){
        if(best3[i] == NULL){
            printf("   [ERROR] string pointer is NULL (i=%d) !\n", i);
        }
        else{
            printf("   [%2d] - %s\n", i+1, best3[i]);
        }
    }
    displayTime(start, end);

//*/
    
    
/*
CLASS_DATA* API_load_students(char * filePath);

int API_save_to_binary_file(CLASS_DATA* pClass, char* filePath);
CLASS_DATA* API_restore_from_binary_file(char* filePath);

void API_display(CLASS_DATA* pClass);
void API_unload(CLASS_DATA* pClass);

char** API_get_best_students(CLASS_DATA* pClass);
char** API_get_best_students_in_course(CLASS_DATA* pClass, char* course);

*/

    return 0;
}
