#include "sort.h"

Student* meilleuresMoyennes(Class *class, int *taille){
    if(class==NULL || taille==NULL){
        exit(0);
    }
    *taille=10;
    if(class->taille<=10){
        *taille = class->taille;
    }
    Student *tab=malloc((*taille)*sizeof(Student));
    if(tab==NULL){
        exit(0);
    }
    int i=0,j=0,indice=0;
    float min=0;
    for(i=0;i<(*taille);i++){
        tab[i] = class->etudiants[i];
    }
    if(class->taille>10){
        for(i=10;i<class->taille;i++){
            min=tab[0].moyenne;
            indice=0;
            for(j=1;j<(*taille);j++){
                if(tab[j].moyenne<min){
                    min=tab[j].moyenne;
                    indice=j;
                }
            }
            if(class->etudiants[i].moyenne>tab[indice].moyenne){
                tab[indice]=class->etudiants[i];
            }
        }
    }
    Student tmp;
    for(i=0;i<(*taille)-1;i++){
        for(j=i+1;j<(*taille);j++){
            if(tab[i].moyenne<tab[j].moyenne){
                tmp=tab[i];
                tab[i]=tab[j];
                tab[j]=tmp;
            }
        }
    }
    return tab;
}

Student* moyennesMatieres(Class *class, char *matierenom, int *taille){
    if(class==NULL || matierenom==NULL || taille==NULL){
        exit(0);
    }
    int i=0,j=0,k=0,r=0,compteur=0,verif=0,indice=0;
    float min=0;
    Student *tab=NULL;
    *taille=0;
    for(i=0;i<class->taille;i++){
        for(j=0;j<class->etudiants[i].taille;j++){
            verif=0;
            if(strcmp(matierenom,class->etudiants[i].matieres[j].nom)==0){
                compteur++;
                verif=1;
            }
            if(compteur>=1 && compteur<=3){
                if(compteur==1){
                    tab=malloc(sizeof(Student));
                }
                else{
                    tab=(Student*) realloc(tab,compteur*sizeof(Student));
                }
                if(tab==NULL){
                    exit(0);
                }
                tab[compteur-1]=class->etudiants[i];
                *taille=compteur;
            }
            else if(verif==1){//compteur>=4
                indice=0;
                for(r=0;r<tab[0].taille;r++){
                    if(strcmp(tab[0].matieres[r].nom,matierenom)==0){
                        min=tab[0].matieres[r].moyenne;
                    }
                }
                for(k=1;k<(*taille);k++){
                    for(r=0;r<tab[k].taille;r++){
                        if(strcmp(tab[k].matieres[r].nom,matierenom)==0){
                            if(tab[k].matieres[r].moyenne < min){
                                indice=k;
                                min=tab[k].matieres[r].moyenne;
                            }
                        }
                    }
                }
                if(class->etudiants[i].matieres[j].moyenne>min){
                    tab[indice]=class->etudiants[i];
                }
            }
        }
    }
    Student tmp;
    float val1=0,val2=0;
    for(i=0;i<(*taille)-1;i++){
        for(j=i+1;j<(*taille);j++){
            for(r=0;r<tab[i].taille;r++){
                if(strcmp(tab[i].matieres[r].nom,matierenom)==0){
                    val1=tab[i].matieres[r].moyenne;
                }
            }
            for(r=0;r<tab[j].taille;r++){
                if(strcmp(tab[j].matieres[r].nom,matierenom)==0){
                    val2=tab[j].matieres[r].moyenne;
                }
            }
            if(val1<val2){
                tmp=tab[i];
                tab[i]=tab[j];
                tab[j]=tmp;
            }
        }
    }

    return tab;
}