#include "files.h"

/**
    @brief Fonction qui restaure les informations d'une promotion d'étudiants depuis un fichier
    @param class La promotion d'étudiants
    @param filePath Le chemin du fichier contenant l'ensemble des données
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*//*
int recoverData(Class* class, char *filePath){
    if(filePath == NULL){
        return 0;
    }
    FILE *file=NULL;
    int i=0,j=0;
    file = fopen(filePath,"rb");
    if(class == NULL || file == NULL){
        return 0;
    }

    fread(class,sizeof(Class),1,file);
    class->students = malloc(class->size*sizeof(Student));
    if(class->students == NULL){
        exit(0);
    }
    fread(class->students,sizeof(Student),class->size,file);

    for(i=0;i<class->size;i++){
        class->students[i].lname = malloc(class->students[i].sizelname*sizeof(char));
        class->students[i].fname = malloc(class->students[i].sizefname*sizeof(char));
        class->students[i].courses = malloc(class->students[i].size*sizeof(Course));
        if(class->students[i].lname==NULL || class->students[i].fname==NULL || class->students[i].courses==NULL){
            exit(0);
        }
        fread(class->students[i].lname,sizeof(char),class->students[i].sizelname,file);
        fread(class->students[i].fname,sizeof(char),class->students[i].sizefname,file);
        fread(class->students[i].courses,sizeof(Course),class->students[i].size,file);
    }

    for(i=0;i<class->size;i++){
        for(j=0;j<class->students[i].size;j++){
            class->students[i].courses[j].name = malloc(class->students[i].courses[j].sizename*sizeof(char));
            class->students[i].courses[j].grades.values = malloc(class->students[i].courses[j].grades.size*sizeof(float));
            if(class->students[i].courses[j].name==NULL || class->students[i].courses[j].grades.values==NULL){
                exit(0);
            }
            fread(class->students[i].courses[j].name,sizeof(char),class->students[i].courses[j].sizename,file);
            fread(class->students[i].courses[j].grades.values,sizeof(float),class->students[i].courses[j].grades.size,file);
        }
    }

    fclose(file);
    return 1;
}
*/

/**
    @brief Fonction qui sauvegarde les informations d'une promotion d'étudiants dans des fichiers
    @param class La promotion d'étudiants
    @param filePath Le chemin du fichier dans lequel sera sauvegardé l'ensemble des données
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*//*
int saveData(Class* class, char *filePath){
    if(filePath == NULL){
        return 0;
    }
    FILE *fileClass=NULL,*fileStudents=NULL,*fileCourses=NULL,*fileGrades=NULL,*file=NULL;
    int i=0,j=0;
    fileClass = fopen("class.bin","wb");
    fileStudents = fopen("students.bin","wb");
    fileCourses = fopen("courses.bin","wb");
    fileGrades = fopen("grades.bin","wb");
    file = fopen(filePath,"wb");
    //Ouverture des fichiers en mode écriture
    if(class == NULL || fileClass == NULL || fileStudents == NULL || fileCourses == NULL || fileGrades == NULL || file == NULL){
        return 0;
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

    fileClass = fopen("class.bin","rb");
    fileStudents = fopen("students.bin","rb");
    fileCourses = fopen("courses.bin","rb");
    fileGrades = fopen("grades.bin","rb");

    if(fileClass == NULL || fileStudents == NULL || fileCourses == NULL || fileGrades == NULL){
        return 0;
    }

    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileClass)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileStudents)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileCourses)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileGrades)) > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }

    fclose(fileClass);
    fclose(fileStudents);
    fclose(fileCourses);
    fclose(fileGrades);
    fclose(file);

    if(remove("class.bin")!=0 || remove("students.bin")!=0 || remove("courses.bin")!=0 || remove("grades.bin")!=0){
        return 0;
    }
    //Suppression des fichiers intermediares

    return 1;
}
*/

/**
    @brief Fonction qui restaure les informations d'une promotion d'étudiants depuis un fichier
    @param class La promotion d'étudiants
    @param filePath Le chemin du fichier contenant l'ensemble des données
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int recoverData(Class* class, char *filePath){
    if(filePath == NULL){
        return 0;
    }
    FILE *file=NULL;
    int i=0,j=0;
    file = fopen(filePath,"rb");
    if(class == NULL || file == NULL){
        return 0;
    }
    class->compare=NULL;

    fread(&class->size,sizeof(int),1,file);
    fread(&class->capacity,sizeof(int),1,file);
    class->students = malloc(class->size*sizeof(Student));
    if(class->students == NULL){
        exit(0);
    }

    for(i=0;i<class->size;i++){
        fread(&class->students[i].id,sizeof(int),1,file);
        fread(&class->students[i].age,sizeof(int),1,file);
        fread(&class->students[i].sizefname,sizeof(int),1,file);
        class->students[i].fname=malloc(class->students[i].sizefname*sizeof(char));
        if(class->students[i].fname == NULL){
            return 0;
        }
        fread(class->students[i].fname,sizeof(char),class->students[i].sizefname,file);
        fread(&class->students[i].sizelname,sizeof(int),1,file);
        class->students[i].lname=malloc(class->students[i].sizelname*sizeof(char));
        if(class->students[i].lname == NULL){
            return 0;
        }
        fread(class->students[i].lname,sizeof(char),class->students[i].sizelname,file);
        fread(&class->students[i].size,sizeof(int),1,file);
        fread(&class->students[i].capacity,sizeof(int),1,file);
        fread(&class->students[i].average,sizeof(float),1,file);
        class->students[i].courses=malloc(class->students[i].size*sizeof(Course));
        if(class->students[i].courses == NULL){
            return 0;
        }
        for(j=0;j<class->students[i].size;j++){
            fread(&class->students[i].courses[j].sizename,sizeof(int),1,file);
            class->students[i].courses[j].name=malloc(class->students[i].courses[j].sizename*sizeof(char));
            if(class->students[i].courses[j].name == NULL){
                return 0;
            }
            fread(class->students[i].courses[j].name,sizeof(char),class->students[i].courses[j].sizename,file);
            fread(&class->students[i].courses[j].average,sizeof(float),1,file);
            fread(&class->students[i].courses[j].coefficient,sizeof(float),1,file);
            fread(&class->students[i].courses[j].grades.size,sizeof(int),1,file);
            fread(&class->students[i].courses[j].grades.capacity,sizeof(int),1,file);
            class->students[i].courses[j].grades.values=malloc(class->students[i].courses[j].grades.size*sizeof(float));
            if(class->students[i].courses[j].grades.values == NULL){
                return 0;
            }
            fread(class->students[i].courses[j].grades.values,sizeof(float),class->students[i].courses[j].grades.size,file);
        }
    }
    
    fclose(file);
    return 1;
}

/**
    @brief Fonction qui sauvegarde les informations d'une promotion d'étudiants dans des fichiers
    @param class La promotion d'étudiants
    @param filePath Le chemin du fichier dans lequel sera sauvegardé l'ensemble des données
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int saveData(Class* class, char *filePath){
    if(filePath == NULL || class == NULL){
        return 0;
    }
    FILE* file = fopen(filePath,"wb");
    if(file == NULL){
        return 0;
    }
    //Ouverture du fichier en mode écriture
    int i=0,j=0;

    fwrite(&class->size,sizeof(int),1,file);
    fwrite(&class->capacity,sizeof(int),1,file);
    for(i=0;i<class->size;i++){
        fwrite(&class->students[i].id,sizeof(int),1,file);
        fwrite(&class->students[i].age,sizeof(int),1,file);
        fwrite(&class->students[i].sizefname,sizeof(int),1,file);
        fwrite(class->students[i].fname,sizeof(char),class->students[i].sizefname,file);
        fwrite(&class->students[i].sizelname,sizeof(int),1,file);
        fwrite(class->students[i].lname,sizeof(char),class->students[i].sizelname,file);
        fwrite(&class->students[i].size,sizeof(int),1,file);
        fwrite(&class->students[i].capacity,sizeof(int),1,file);
        fwrite(&class->students[i].average,sizeof(float),1,file);
        for(j=0;j<class->students[i].size;j++){
            fwrite(&class->students[i].courses[j].sizename,sizeof(int),1,file);
            fwrite(class->students[i].courses[j].name,sizeof(char),class->students[i].courses[j].sizename,file);
            fwrite(&class->students[i].courses[j].average,sizeof(float),1,file);
            fwrite(&class->students[i].courses[j].coefficient,sizeof(float),1,file);
            fwrite(&class->students[i].courses[j].grades.size,sizeof(int),1,file);
            fwrite(&class->students[i].courses[j].grades.capacity,sizeof(int),1,file);
            fwrite(class->students[i].courses[j].grades.values,sizeof(float),class->students[i].courses[j].grades.size,file);
        }
    }

    fclose(file);
    return 1;
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