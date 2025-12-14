#include "display.h"

/**
    @brief Fonction qui affiche toutes les informations d'une promotion d'étudiants
    @param class La promotion d'étudiants
*/
void displayClass(Class class){
    int i=0,j=0,k=0;
    Student allcourses=class.students[class.size-1];
    printf("\n--> RAYANE MEHANNI <--\n\nMatieres : %d\n\n",allcourses.size);
    for(i=0;i<allcourses.size;i++){
        printf("%s, Coefficient : %f\n",allcourses.courses[i].name,allcourses.courses[i].coefficient);
    }
    printf("\nPromotion : %d etudiants\n\n",class.size-1);
    for(i=0;i<class.size-1;i++){//On s'arrête à class.size-2 car class.size-1 contient l'étudiant vide qui a toutes les matières pour garder une trace sur ces dernières
        printf("%d, %s %s, %d ans / Moyenne : %f\n-> Matieres : \n\n",class.students[i].id,class.students[i].lname,class.students[i].fname,class.students[i].age,class.students[i].average);
        for(j=0;j<class.students[i].size;j++){
            printf("--> %s / Coefficient : %f / Moyenne : %f\n----> Notes : ",class.students[i].courses[j].name,class.students[i].courses[j].coefficient,class.students[i].courses[j].average);
            for(k=0;k<class.students[i].courses[j].grades.size;k++){
                printf("%f, ",class.students[i].courses[j].grades.values[k]);
            }
            printf("\n\n");
        }
        printf("\n\n");
    }
}

/**
    @brief Fonction qui affiche un tableau d'étudiants
    @param array Le tableau d'étudiants
    @param size la taille du tableau
    @param coursename Le nom d'une matière (s'il y en a)
*/
void displayStudents(Student* array, int size, char* coursename){
    int i=0,j=0;
    if(array==NULL){
        return ;
    }
    for(i=0;i<size;i++){
        printf("%d. %d, %s %s, %d ans / Moyenne : %f\n",i+1,array[i].id,array[i].lname,array[i].fname,array[i].age,array[i].average);
        if(coursename!=NULL){
            for(j=0;j<array[i].size;j++){
                if(strcmp(array[i].courses[j].name,coursename)==0){
                    printf("--> %s / Coefficient : %f / Moyenne : %f\n",array[i].courses[j].name,array[i].courses[j].coefficient,array[i].courses[j].average);
                }
            }
        }
        printf("\n");
    }
}
