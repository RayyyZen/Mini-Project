#include "donnees.h"

void ajoutEtudiant(Class *class, char *ligne){
    if(class==NULL){
        exit(0);
    }
    int id=0,age=0,indice=class->taille;
    char prenom[50],nom[50];
    sscanf(ligne, "%d;%[^;];%[^;];%d", &id,prenom,nom,&age);
    if(class->capacite == 0){
        class->etudiants=malloc(sizeof(Student));
        if(class->etudiants == NULL){
            exit(0);
        }
        class->capacite = 1;
    }
    else if(class->taille == class->capacite) {
        class->capacite *= 2;
        class->etudiants = (Student*) realloc(class->etudiants,class->capacite*sizeof(Student));
        if(class->etudiants == NULL){
            exit(0);
        }
    }

    class->taille++;
    class->etudiants[indice] = constructeurStudent();
    class->etudiants[indice].id=id;
    class->etudiants[indice].age=age;
    class->etudiants[indice].nomtaille=strlen(nom)+1;
    class->etudiants[indice].prenomtaille=strlen(prenom)+1;
    class->etudiants[indice].nom=malloc(sizeof(char)*(strlen(nom)+1));
    strcpy(class->etudiants[indice].nom,nom);
    class->etudiants[indice].prenom=malloc(sizeof(char)*(strlen(prenom)+1));
    strcpy(class->etudiants[indice].prenom,prenom);
}

void ajoutMatiere(Student *student, char *ligne){
    if(student==NULL){
        exit(0);
    }
    int indice=student->taille;
    float coeff=0;
    char nom[50];
    sscanf(ligne, "%[^;];%f", nom,&coeff);
    if(student->capacite == 0){
        student->matieres=malloc(sizeof(Course));
        if(student->matieres == NULL){
            exit(0);
        }
        student->capacite = 1;
    }
    else if(student->taille == student->capacite) {
        student->capacite *= 2;
        student->matieres = (Course*) realloc(student->matieres,student->capacite*sizeof(Course));
        if(student->matieres == NULL){
            exit(0);
        }
    }

    student->taille++;
    student->matieres[indice] = constructeurCourse();
    student->matieres[indice].coefficient=coeff;
    student->matieres[indice].nomtaille=strlen(nom)+1;
    student->matieres[indice].nom=malloc(sizeof(char)*(strlen(nom)+1));
    strcpy(student->matieres[indice].nom,nom);
}

void ajoutNote(Class *class, Student *totalmatieres, pArbre a, char *ligne){
    if(class==NULL){
        exit(0);
    }
    int id=0,indice=0,i=0,verif=0;
    float note=0;
    char nom[50];
    sscanf(ligne, "%d;%[^;];%f", &id,nom,&note);
    Student *etu = rechercheNoeud(a,id);
    if(etu == NULL){
        exit(0);
    }

    if(etu->capacite == 0){
        etu->matieres = malloc(sizeof(Course));
        etu->capacite = 1;
        etu->matieres[etu->taille] = constructeurCourse();
        for(i=0;i<totalmatieres->taille;i++){
            if(strcmp(totalmatieres->matieres[i].nom,nom) == 0){
                etu->matieres[etu->taille].nomtaille=totalmatieres->matieres[i].nomtaille;
                etu->matieres[etu->taille].nom=malloc(sizeof(char)*etu->matieres[etu->taille].nomtaille);
                strcpy(etu->matieres[etu->taille].nom,nom);
                etu->matieres[etu->taille].coefficient=totalmatieres->matieres[i].coefficient;
                etu->matieres[etu->taille].moyenne=note;
                etu->matieres[etu->taille].notes = constructeurGrades();
                etu->matieres[etu->taille].notes.valeurs = malloc(sizeof(float));
                etu->matieres[etu->taille].notes.capacite = 1;
                etu->matieres[etu->taille].notes.valeurs[etu->matieres[etu->taille].notes.taille] = note;
                etu->matieres[etu->taille].notes.taille++;
            }
        }
        etu->moyenne = (etu->moyenne*etu->taille+note)/(etu->taille+1);
        etu->taille++;
    }
    else{
        for(i=0;i<etu->taille;i++){
            if(strcmp(etu->matieres[i].nom,nom) == 0){
                indice=i;
                verif=1;
                break;
            }
        }
        if(verif==0){
            if(etu->capacite == etu->taille){
                etu->capacite *= 2;
                etu->matieres = (Course*) realloc(etu->matieres,etu->capacite*sizeof(Course));
            }
            etu->matieres[etu->taille] = constructeurCourse();
            for(i=0;i<totalmatieres->taille;i++){
                if(strcmp(totalmatieres->matieres[i].nom,nom) == 0){
                    etu->matieres[etu->taille].nomtaille=totalmatieres->matieres[i].nomtaille;
                    etu->matieres[etu->taille].nom=malloc(sizeof(char)*etu->matieres[etu->taille].nomtaille);
                    strcpy(etu->matieres[etu->taille].nom,nom);
                    etu->matieres[etu->taille].coefficient=totalmatieres->matieres[i].coefficient;
                    etu->matieres[etu->taille].moyenne=note;
                    etu->matieres[etu->taille].notes = constructeurGrades();
                    etu->matieres[etu->taille].notes.valeurs = malloc(sizeof(float));
                    etu->matieres[etu->taille].notes.capacite = 1;
                    etu->matieres[etu->taille].notes.valeurs[etu->matieres[etu->taille].notes.taille] = note;
                    etu->matieres[etu->taille].notes.taille++;
                }
            }
            etu->moyenne = (etu->moyenne*etu->taille+note)/(etu->taille+1);
            etu->taille++;
        }
        else{
            int ancienne = etu->matieres[indice].moyenne;
            etu->matieres[indice].moyenne=(etu->matieres[indice].moyenne*etu->taille+note)/(etu->taille+1);
            if(etu->matieres[indice].notes.capacite == 0){
                etu->matieres[indice].notes.valeurs = malloc(sizeof(float));
                etu->matieres[indice].notes.capacite = 1;
                etu->matieres[indice].notes.valeurs[etu->matieres[indice].notes.taille] = note;
                etu->matieres[indice].notes.taille++;
            }
            else if(etu->matieres[indice].notes.capacite > etu->matieres[indice].notes.taille){
                etu->matieres[indice].notes.valeurs[etu->matieres[indice].notes.taille] = note;
                etu->matieres[indice].notes.taille++;
            }
            else{
                etu->matieres[indice].notes.capacite*=2;
                etu->matieres[indice].notes.valeurs = (float*) realloc(etu->matieres[indice].notes.valeurs,etu->matieres[indice].notes.capacite*sizeof(float));
                etu->matieres[indice].notes.valeurs[etu->matieres[indice].notes.taille] = note;
                etu->matieres[indice].notes.taille++;
            }
            etu->moyenne = (etu->moyenne*etu->taille+etu->matieres[indice].moyenne-ancienne)/etu->taille;
        }
    }
}

void stockageDonnees(Class *class, char *chemin){
    pArbre a=NULL;
    FILE *fichier = fopen(chemin,"r");
    char ligne[100];
    char *verif=NULL;
    if(fichier==NULL){
        exit(1);
    }
    Student* totalmatieres = malloc(sizeof(Student));
    if(totalmatieres==NULL){
        exit(0);
    }
    *totalmatieres = constructeurStudent();
    do{
        verif=fgets(ligne,sizeof(ligne),fichier);
    }while(verif!=NULL && strcmp(ligne,"ETUDIANTS\n")!=0);
    fgets(ligne,sizeof(ligne),fichier);
    
    while(fgets(ligne,sizeof(ligne),fichier)!=NULL && ligne[0]!='\n'){
        ajoutEtudiant(class,ligne);
    }

    for(int i=0;i<class->taille;i++){
        a=ajoutNoeud(a,&class->etudiants[i]);
    }

    do{
        verif=fgets(ligne,sizeof(ligne),fichier);
    }while(verif!=NULL && strcmp(ligne,"MATIERES\n")!=0);
    fgets(ligne,sizeof(ligne),fichier);

    while(fgets(ligne,sizeof(ligne),fichier)!=NULL && ligne[0]!='\n'){
        ajoutMatiere(totalmatieres,ligne);
    }

    do{
        verif=fgets(ligne,sizeof(ligne),fichier);
    }while(verif!=NULL && strcmp(ligne,"NOTES\n")!=0);
    fgets(ligne,sizeof(ligne),fichier);
    
    while(fgets(ligne,sizeof(ligne),fichier)!=NULL && ligne[0]!='\n'){
        printf("%s",ligne);
        ajoutNote(class,totalmatieres,a,ligne);
    }
    fclose(fichier);
}