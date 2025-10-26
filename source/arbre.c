#include "arbre.h"

pArbre creerArbre(Student *etu){
    pArbre a=malloc(sizeof(Arbre));
    if(a==NULL){
        exit(0);
    }
    a->fg=NULL;
    a->fd=NULL;
    a->etu=etu;
    return a;
}

void afficher(pArbre a){
    if(a!=NULL){
        printf("%d\n",a->etu->id);
        afficher(a->fg);
        afficher(a->fd);
    }
}

pArbre ajoutNoeud(pArbre a, Student *etu){
    if(a==NULL){
        return creerArbre(etu);
    }
    else if(a->etu->id > etu->id){
        a->fg = ajoutNoeud(a->fg,etu);
    }
    else if(a->etu->id < etu->id){
        a->fd = ajoutNoeud(a->fd,etu);
    }
    return a;
}

Student* rechercheNoeud(pArbre a, int id){
    if(a==NULL){
        return NULL;
    }
    while(a!=NULL){
        if(a->etu->id < id){
            a=a->fd;
        }
        else if(a->etu->id > id){
            a=a->fg;
        }
        else{
            return a->etu;
        }
    }
    return NULL;
}

void supprimerFilsGauche(pArbre a){
    if(a==NULL || a->fg==NULL){
        return;
    }
    else{
        if(a->fg->fg!=NULL){
            supprimerFilsGauche(a->fg);
        }
        if(a->fg->fd!=NULL){
            supprimerFilsDroit(a->fg);
        }
        free(a->fg);
        a->fg=NULL;
    }
}

void supprimerFilsDroit(pArbre a){
    if(a==NULL || a->fd==NULL){
        return;
    }
    else{
        if(a->fd->fg!=NULL){
            supprimerFilsGauche(a->fd);
        }
        if(a->fd->fd!=NULL){
            supprimerFilsDroit(a->fd);
        }
        free(a->fd);
        a->fd=NULL;
    }
}

pArbre destructeurArbre(pArbre a){
    if(a!=NULL){
        supprimerFilsDroit(a);
        supprimerFilsGauche(a);
        free(a);
        a=NULL;
    }
    return a;
}