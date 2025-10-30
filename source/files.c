#include "files.h"

void sauvegarder(Class *class){
    FILE *promotion=NULL,*etudiants=NULL,*matieres=NULL,*notes=NULL;
    int i=0,j=0;
    promotion = fopen("Data/class.bin","wb");
    etudiants = fopen("Data/students.bin","wb");
    matieres = fopen("Data/courses.bin","wb");
    notes = fopen("Data/grades.bin","wb");
    if(promotion == NULL || etudiants == NULL || matieres == NULL || notes == NULL){
        exit(2);
    }

    for(i=0;i<class->taille;i++){
        for(j=0;j<class->etudiants[i].taille;j++){
            fwrite(class->etudiants[i].matieres[j].nom,sizeof(char),class->etudiants[i].matieres[j].nomtaille,notes);
            free(class->etudiants[i].matieres[j].nom);
            class->etudiants[i].matieres[j].nom=NULL;

            fwrite(class->etudiants[i].matieres[j].notes.valeurs,sizeof(float),class->etudiants[i].matieres[j].notes.taille,notes);
            free(class->etudiants[i].matieres[j].notes.valeurs);
            class->etudiants[i].matieres[j].notes.valeurs=NULL;
        }
        fwrite(class->etudiants[i].nom,sizeof(char),class->etudiants[i].nomtaille,matieres);
        free(class->etudiants[i].nom);
        class->etudiants[i].nom=NULL;

        fwrite(class->etudiants[i].prenom,sizeof(char),class->etudiants[i].prenomtaille,matieres);
        free(class->etudiants[i].prenom);
        class->etudiants[i].prenom=NULL;

        fwrite(class->etudiants[i].matieres,sizeof(Course),class->etudiants[i].taille,matieres);
        free(class->etudiants[i].matieres);
        class->etudiants[i].matieres=NULL;
        
    }
    fwrite(class->etudiants,sizeof(Student),class->taille,etudiants);
    free(class->etudiants);
    class->etudiants=NULL;
    fwrite(class,sizeof(Class),1,promotion);

    fclose(promotion);
    fclose(etudiants);
    fclose(matieres);
    fclose(notes);
}

void restaurer(Class *class){
    FILE *promotion=NULL,*etudiants=NULL,*matieres=NULL,*notes=NULL;
    int i=0,j=0;
    promotion = fopen("Data/class.bin","rb");
    etudiants = fopen("Data/students.bin","rb");
    matieres = fopen("Data/courses.bin","rb");
    notes = fopen("Data/grades.bin","rb");
    if(promotion == NULL || etudiants == NULL || matieres == NULL || notes == NULL){
        exit(2);
    }

    fread(class,sizeof(Class),1,promotion);
    class->etudiants = malloc(class->taille*sizeof(Student));
    if(class->etudiants == NULL){
        exit(0);
    }
    fread(class->etudiants,sizeof(Student),class->taille,etudiants);

    for(i=0;i<class->taille;i++){
        class->etudiants[i].nom = malloc(class->etudiants[i].nomtaille*sizeof(char));
        class->etudiants[i].prenom = malloc(class->etudiants[i].prenomtaille*sizeof(char));
        class->etudiants[i].matieres = malloc(class->etudiants[i].taille*sizeof(Course));
        if(class->etudiants[i].nom==NULL || class->etudiants[i].prenom==NULL || class->etudiants[i].matieres==NULL){
            exit(0);
        }
        fread(class->etudiants[i].nom,sizeof(char),class->etudiants[i].nomtaille,matieres);
        fread(class->etudiants[i].prenom,sizeof(char),class->etudiants[i].prenomtaille,matieres);
        fread(class->etudiants[i].matieres,sizeof(Course),class->etudiants[i].taille,matieres);
        for(j=0;j<class->etudiants[i].taille;j++){
            class->etudiants[i].matieres[j].nom = malloc(class->etudiants[i].matieres[j].nomtaille*sizeof(char));
            class->etudiants[i].matieres[j].notes.valeurs = malloc(class->etudiants[i].matieres[j].notes.taille*sizeof(float));
            if(class->etudiants[i].matieres[j].nom==NULL || class->etudiants[i].matieres[j].notes.valeurs==NULL){
                exit(0);
            }
            fread(class->etudiants[i].matieres[j].nom,sizeof(char),class->etudiants[i].matieres[j].nomtaille,notes);
            fread(class->etudiants[i].matieres[j].notes.valeurs,sizeof(float),class->etudiants[i].matieres[j].notes.taille,notes);
        }
    }

    fclose(promotion);
    fclose(etudiants);
    fclose(matieres);
    fclose(notes);
}