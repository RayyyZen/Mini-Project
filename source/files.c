#include "files.h"

/**
    @brief Fonction qui sauvegarde les informations d'une promotion d'étudiants dans des fichiers
    @param class La promotion d'étudiants
*/
void saveData(Class* class){
    FILE *fileClass=NULL,*fileStudents=NULL,*fileCourses=NULL,*fileGrades=NULL;
    int i=0,j=0;
    fileClass = fopen("Data/class.bin","wb");
    fileStudents = fopen("Data/students.bin","wb");
    fileCourses = fopen("Data/courses.bin","wb");
    fileGrades = fopen("Data/grades.bin","wb");
    //Ouverture des fichiers en mode écriture
    if(fileClass == NULL || fileStudents == NULL || fileCourses == NULL || fileGrades == NULL){
        exit(2);
    }

    for(i=0;i<class->size;i++){
        for(j=0;j<class->students[i].size;j++){
            fwrite(class->students[i].courses[j].name,sizeof(char),class->students[i].courses[j].sizename,fileGrades);
            free(class->students[i].courses[j].name);
            class->students[i].courses[j].name=NULL;

            fwrite(class->students[i].courses[j].grades.values,sizeof(float),class->students[i].courses[j].grades.size,fileGrades);
            //free(class->students[i].courses[j].grades.values);
            //class->students[i].courses[j].grades.values=NULL;
            destroyGrades(&class->students[i].courses[j].grades);
        }
        fwrite(class->students[i].lname,sizeof(char),class->students[i].sizelname,fileCourses);
        free(class->students[i].lname);
        class->students[i].lname=NULL;

        fwrite(class->students[i].fname,sizeof(char),class->students[i].sizefname,fileCourses);
        free(class->students[i].fname);
        class->students[i].fname=NULL;

        fwrite(class->students[i].courses,sizeof(Course),class->students[i].size,fileCourses);
        //free(class->students[i].courses);
        //class->students[i].courses=NULL;
        class->students[i].courses=destroyCourse(class->students[i].courses);
    }
    fwrite(class->students,sizeof(Student),class->size,fileStudents);
    //free(class->students);
    //class->students=NULL;
    class->students=destroyStudent(class->students);
    fwrite(class,sizeof(Class),1,fileClass);
    destroyClass(class);

    fclose(fileClass);
    fclose(fileStudents);
    fclose(fileCourses);
    fclose(fileGrades);
}

/**
    @brief Fonction qui restaure les informations d'une promotion d'étudiants depuis des fichiers
    @param class La promotion d'étudiants
*/
void recoverData(Class* class){
    FILE *fileClass=NULL,*fileStudents=NULL,*fileCourses=NULL,*fileGrades=NULL;
    int i=0,j=0;
    fileClass = fopen("Data/class.bin","rb");
    fileStudents = fopen("Data/students.bin","rb");
    fileCourses = fopen("Data/courses.bin","rb");
    fileGrades = fopen("Data/grades.bin","rb");
    if(fileClass == NULL || fileStudents == NULL || fileCourses == NULL || fileGrades == NULL){
        exit(2);
    }

    fread(class,sizeof(Class),1,fileClass);
    class->students = malloc(class->size*sizeof(Student));
    if(class->students == NULL){
        exit(0);
    }
    fread(class->students,sizeof(Student),class->size,fileStudents);

    for(i=0;i<class->size;i++){
        class->students[i].lname = malloc(class->students[i].sizelname*sizeof(char));
        class->students[i].fname = malloc(class->students[i].sizefname*sizeof(char));
        class->students[i].courses = malloc(class->students[i].size*sizeof(Course));
        if(class->students[i].lname==NULL || class->students[i].fname==NULL || class->students[i].courses==NULL){
            exit(0);
        }
        fread(class->students[i].lname,sizeof(char),class->students[i].sizelname,fileCourses);
        fread(class->students[i].fname,sizeof(char),class->students[i].sizefname,fileCourses);
        fread(class->students[i].courses,sizeof(Course),class->students[i].size,fileCourses);
        for(j=0;j<class->students[i].size;j++){
            class->students[i].courses[j].name = malloc(class->students[i].courses[j].sizename*sizeof(char));
            class->students[i].courses[j].grades.values = malloc(class->students[i].courses[j].grades.size*sizeof(float));
            if(class->students[i].courses[j].name==NULL || class->students[i].courses[j].grades.values==NULL){
                exit(0);
            }
            fread(class->students[i].courses[j].name,sizeof(char),class->students[i].courses[j].sizename,fileGrades);
            fread(class->students[i].courses[j].grades.values,sizeof(float),class->students[i].courses[j].grades.size,fileGrades);
        }
    }

    fclose(fileClass);
    fclose(fileStudents);
    fclose(fileCourses);
    fclose(fileGrades);
}

/**
    @brief Fonction qui checke si un fichier existe
    @param path Le chemin d'un fichier
    @retval 0 Le fichier n'existe pas
    @retval 1 Le fichier existe
*/
int checkFile(char *path){
    FILE *file=fopen(path,"rb");
    if(file==NULL){
        return 0;
    }
    else{
        fclose(file);
        return 1;
    }
}