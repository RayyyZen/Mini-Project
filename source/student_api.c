#include "student_api.h"
#include "sort.h"

/**
    @brief Fonction qui traite un fichier et remplit une promotion d'étudiants
    @param filePath Une chaine de caractères contenant le chemin du fichier à traiter
    @return Un pointeur vers la promotion d'étudiants
*/
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

/**
    @brief Fonction qui sauvegarde les informations d'une promotion d'étudiants dans un fichier
    @param pClass La promotion d'étudiants
    @param filePath Le chemin du fichier dans lequel sera sauvegardé l'ensemble des données
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int API_save_to_binary_file(CLASS_DATA* pClass, char* filePath){
    Class* class=(Class*) pClass;
    return saveData(class,filePath);
}

/**
    @brief Fonction qui restaure les informations d'une promotion d'étudiants depuis un fichier
    @param filePath Le chemin du fichier contenant l'ensemble des données
    @return Un pointeur vers la promotion d'étudiants
*/
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

/**
    @brief Fonction qui affiche toutes les informations d'une promotion d'étudiants
    @param pClass La promotion d'étudiants
*/
void API_display(CLASS_DATA* pClass){
    Class* class=(Class*) pClass;
    if(class==NULL){
        exit(0);
    }
    displayClass(*class);
}

/**
    @brief Fonction qui libère toute la mémoire allouée
    @param pClass Un pointeur vers la promotion d'étudiants
*/
void API_unload(CLASS_DATA* pClass){
    Class* class=(Class*) pClass;
    class=dataDestroy(class);
}

/**
    @brief Fonction qui remplit un tableau 2D de chaine de caractère avec les informations des étudiants contenues dans un tableau
    @param pArray Un tableau d'étudiants
    @param size La taille du tableau d'étudiants
    @return Un tableau 2D de chaine de caractère contenant les informations des étudiants du tableau passé en paramètre
*/
char** Best_students(CLASS_DATA* pArray, int size){
    Student *array=(Student*) pArray;
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

/**
    @brief Fonction qui retourne un tableau des 10 étudiants avec la meilleure moyenne de la promotion
    @param pClass La promotion d'étudiants
    @return Un tableau 2D de chaine de caractère contenant les informations des 10 étudiants avec la meilleure moyenne de la promotion
*/
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

/**
    @brief Fonction qui retourne un tableau des 3 étudiants avec la meilleure moyenne de la promotion dans une certaine matière
    @param pClass La promotion d'étudiants
    @param course Le nom d'une matière
    @return Un tableau 2D de chaine de caractère contenant les informations des 3 étudiants avec la meilleure moyenne de la promotion dans une certaine matière
*/
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

/**
    @brief Fonction qui change le mode de tri des étudiants de la promotion
    @param pClass La promotion d'étudiants
    @param mode Le nouveau mode de tri
    @retval 1 Le changement du mode de tri s'est passé avec succés
    @retval 0 Le changement du mode de tri a échoué
*/
int API_set_sorting_mode(CLASS_DATA* pClass, int mode){
    Class* class=(Class*) pClass;
    if(class==NULL){
        return 0;
    }

    switch(mode){
        case ALPHA_FIRST_NAME :
            class->compare=compareFirstName;
            break;
        case ALPHA_LAST_NAME :
            class->compare=compareLastName;
            break;
        case AVERAGE :
            class->compare=compareAverage;
            break;
        case MINIMUM :
            class->compare=compareMinimum;
            break;
        default :
            return 0;
    }
    return 1;
}

/**
    @brief Fonction qui retourne un tableau des 10 étudiants triés selon un certain mode
    @param pClass La promotion d'étudiants
    @return Un tableau 2D de chaine de caractère contenant les informations des 10 étudiants triés selon un certain mode
*/
char** API_sort_students(CLASS_DATA* pClass){
    Class* class=(Class*) pClass;
    if(class==NULL || class->students==NULL || class->size<=0){
        return NULL;
    }
    if(class->compare==NULL){
        class->compare=compareAverage;
        //Par default
    }

    Student tmp;
    int size=SIZE_TOP1,i=0,j=0;
    if(class->size<size){
        size=class->size;
    }
    for(i=0;i<class->size-2;i++){//Car dans class->size-1 il y a l'etudiant vide qui contient les matières de la promotion
        for(j=i+1;j<class->size-1;j++){
            if(class->compare(&class->students[i],&class->students[j])==1){
                tmp=class->students[i];
                class->students[i]=class->students[j];
                class->students[j]=tmp;
            }
        }
    }

    Student* array=malloc(size*sizeof(Student));
    if(array==NULL){
        return NULL;
    }
    for(i=0;i<size;i++){
        array[i]=class->students[i];
    }
    return Best_students(array,size);
}