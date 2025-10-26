#include "arbre.h"

pArbre constructeurArbre(){
    pArbre parbre;
    parbre.etu=NULL;
    parbre.fg=NULL;
    parbre.fd=NULL;
    return parbre;
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