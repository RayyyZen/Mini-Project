#include "student_api.h"

CLASS_DATA* API_load_students(char* filePath){
    Class* class=malloc(sizeof(Class));
    if(class==NULL){
        return NULL;
    }
    *class=buildClass();
    if(dataStorage(class,filePath)==0){
        return NULL;
    }
    return class;
}

int API_save_to_binary_file(CLASS_DATA* pClass, char* filePath){
    Class* class=(Class*) pClass;
    return saveData(class,filePath);
}

CLASS_DATA* API_restore_from_binary_file(char* filePath){
    Class* class=malloc(sizeof(Class));
    if(class==NULL){
        return NULL;
    }
    *class=buildClass();
    if(recoverData(class,filePath)==0){
        return NULL;
    }
    return class;
}

void API_display(CLASS_DATA* pClass){
    Class* class=(Class*) pClass;
    if(class==NULL){
        exit(0);
    }
    displayClass(*class);
}

void API_unload(CLASS_DATA* pClass){
    Class* class=(Class*) pClass;
    class=dataDestroy(class);
}

char** Best_students(Student* array, int size){
    if(array==NULL){
        return NULL;
    }
    int i=0,length=0;
    char** bestStudents=NULL;
    bestStudents=malloc(size*sizeof(char*));
    if(bestStudents==NULL){
        return NULL;
    }
    for(i=0;i<size;i++){
        length=snprintf(NULL,0,"%d. %d, %s %s, %d ans / Moyenne : %f",i+1,array[i].id,array[i].lname,array[i].fname,array[i].age,array[i].average);
        bestStudents[i]=malloc((length+1)*sizeof(char));
        if(bestStudents[i]==NULL){
            return NULL;
        }
        snprintf(bestStudents[i],length+1,"%d. %d, %s %s, %d ans / Moyenne : %f",i+1,array[i].id,array[i].lname,array[i].fname,array[i].age,array[i].average);
    }
    return bestStudents;
}

char** API_get_best_students(CLASS_DATA* pClass){
    Class* class=(Class*) pClass;
    if(class==NULL){
        return NULL;
    }
    int size=0;
    Student* array=bestAverages(class,&size,SIZE_TOP1);
    if(array==NULL || size<=0){
        return NULL;
    }
    char** bestStudents=Best_students(array,size);
    return bestStudents;
}

char** API_get_best_students_in_course(CLASS_DATA* pClass, char* course){
    Class* class=(Class*) pClass;
    if(class==NULL || course==NULL){
        return NULL;
    }
    int size=0;
    Student* array=bestCourseAverages(class,course,&size,SIZE_TOP2);
    if(array==NULL || size<=0){
        return NULL;
    }
    char** bestStudents=Best_students(array,size);
    return bestStudents;
}