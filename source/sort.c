#include "sort.h"

/**
    @brief Fonction qui retourne un tableau des étudiants avec la meilleure moyenne de la promotion
    @param class La promotion d'étudiants
    @param size Un pointeur sur la taille du tableau qu'on va créer
    @param max Le maximum d'étudiants à retourner
    @return Le tableau d'étudiants crée
*/
Student* bestAverages(Class* class, int* size, int max){
    if(class==NULL || size==NULL){
        return NULL;
    }
    *size=max;
    if(class->size<=max){
        *size = class->size;
    }
    Student *array=malloc((*size)*sizeof(Student));
    if(array==NULL){
        return NULL;
    }
    int i=0,j=0,index=0;
    float min=0;
    for(i=0;i<(*size);i++){
        array[i] = class->students[i];
    }
    if(class->size>max){
        for(i=max;i<class->size;i++){
            min=array[0].average;
            index=0;
            for(j=1;j<(*size);j++){//Recherche de la plus petite moyenne du tableau "array"
                if(array[j].average<min){
                    min=array[j].average;
                    index=j;
                }
            }
            if(class->students[i].average>array[index].average){
                array[index]=class->students[i];
            }
        }
    }

    Student tmp;
    for(i=0;i<(*size)-1;i++){
        for(j=i+1;j<(*size);j++){
            if(array[i].average<array[j].average){
                tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }
        }
    }
    //Tri décroissant en fonction de la moyenne des étudiants

    return array;
}

/**
    @brief Fonction qui retourne un tableau des 3 étudiants avec la meilleure moyenne de la promotion dans une certaine matière
    @param class La promotion d'étudiants
    @param coursename Le nom d'une matière
    @param size Un pointeur sur la taille du tableau qu'on va créer
    @param max Le maximum d'étudiants à retourner
    @return Le tableau d'étudiants crée
*/
Student* bestCourseAverages(Class* class, char* coursename, int* size, int max){
    if(class==NULL || coursename==NULL || size==NULL){
        return NULL;
    }
    int i=0,j=0,k=0,r=0,counter=0,verif=0,index=0;
    float min=0;
    Student *array=NULL;
    *size=0;
    for(i=0;i<class->size;i++){
        for(j=0;j<class->students[i].size;j++){
            verif=0;
            if(strcmp(coursename,class->students[i].courses[j].name)==0){
                counter++;
                verif=1;
            }
            if(counter>=1 && counter<=max){
                if(counter==1){
                    array=malloc(sizeof(Student));
                }
                else{
                    array=(Student*) realloc(array,counter*sizeof(Student));
                }
                if(array==NULL){
                    return NULL;
                }
                array[counter-1]=class->students[i];
                *size=counter;
            }
            else if(verif==1){//counter>max
                index=0;
                for(r=0;r<array[0].size;r++){
                    if(strcmp(array[0].courses[r].name,coursename)==0){
                        min=array[0].courses[r].average;
                    }
                }
                for(k=1;k<(*size);k++){//Recherche de la plus petite moyenne de la matière "coursename" dans le tableau "array"
                    for(r=0;r<array[k].size;r++){
                        if(strcmp(array[k].courses[r].name,coursename)==0){
                            if(array[k].courses[r].average < min){
                                index=k;
                                min=array[k].courses[r].average;
                            }
                        }
                    }
                }
                if(class->students[i].courses[j].average>min){
                    array[index]=class->students[i];
                }
            }
        }
    }

    Student tmp;
    float val1=0,val2=0;
    for(i=0;i<(*size)-1;i++){
        for(j=i+1;j<(*size);j++){
            for(r=0;r<array[i].size;r++){
                if(strcmp(array[i].courses[r].name,coursename)==0){
                    val1=array[i].courses[r].average;
                }
            }
            for(r=0;r<array[j].size;r++){
                if(strcmp(array[j].courses[r].name,coursename)==0){
                    val2=array[j].courses[r].average;
                }
            }
            if(val1<val2){
                tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }
        }
    }
    //Tri décroissant en fonction de la moyenne des étudiants dans la matière

    return array;
}

int compareStrings(char *str1, char *str2){
    if(str1 == NULL || str2 == NULL){
        exit(3);
    }
    int counter=0;
    while(str1[counter]!='\0' && str2[counter]!='\0'){
        if(str1[counter]<str2[counter]){
            return -1; 
        }
        else if(str1[counter]>str2[counter]){
            return 1;
        }
        counter++;
    }
    if(str1[counter]=='\0' && str2[counter]!='\0'){
        return -1;
    }
    else if(str1[counter]!='\0' && str2[counter]=='\0'){
        return 1;
    }
    return 0;
}

int compareFirstName(Student* student1, Student* student2){
    if(student1 == NULL || student2 == NULL || student1->fname == NULL || student2->fname == NULL){
        exit(2);
    }
    return compareStrings(student1->fname,student2->fname);
}

int compareLastName(Student* student1, Student* student2){
    if(student1 == NULL || student2 == NULL || student1->lname == NULL || student2->lname == NULL){
        exit(2);
    }
    return compareStrings(student1->lname,student2->lname);
}

int compareAverage(Student* student1, Student* student2){
    if(student1 == NULL || student2 == NULL){
        exit(2);
    }

    if(student1->average > student2->average){
        return -1;
    }
    else if(student1->average < student2->average){
        return 1;
    }
    return 0;
}

float getMinimumAverage(Student* std){
    if(std == NULL){
        exit(2);
    }
    if(std->courses==NULL || std->size<=0){
        return -1;
    }
    int i=0;
    float min=std->courses[0].average;
    for(i=1;i<std->size;i++){
        if(std->courses[i].average<min){
            min=std->courses[i].average;
        }
    }
    return min;
}

int compareMinimum(Student* student1, Student* student2){
    if(student1 == NULL || student2 == NULL){
        exit(2);
    }

    if(getMinimumAverage(student1) > getMinimumAverage(student2)){
        return -1;
    }
    else if(getMinimumAverage(student1) < getMinimumAverage(student2)){
        return 1;
    }
    return 0;
}