#include "tree.h"

/**
    @brief Fonction qui crée un noeud de l'arbre
    @param std L'adresse de l'étudiant stockée dans le noeud crée
    @return Le noeud de l'arbre crée
*/
pTree createTree(Student* std){
    pTree tree=malloc(sizeof(Tree));
    if(tree==NULL){
        exit(0);
    }
    tree->left=NULL;
    tree->right=NULL;
    tree->std=std;
    return tree;
}

/**
    @brief Fonction qui affiche les identifiants des étudiants stockées dans les noeuds de l'arbre
    @param tree L'arbre binaire de recherche contenant les adresses des étudiants
*/
void display(pTree tree){
    if(tree!=NULL){
        printf("%d\n",tree->std->id);
        display(tree->left);
        display(tree->right);
    }
}

/**
    @brief Fonction qui ajoute un noeud à l'arbre binaire de recherche
    @param tree L'arbre dans lequel le noeud est ajouté
    @param std L'adresse de l'étudiant ajouté dans l'arbre
    @return L'arbre binaire de recherche contenant les adresses des étudiants
*/
pTree addNode(pTree tree, Student* std){
    if(tree==NULL){
        return createTree(std);
    }
    else if(tree->std->id > std->id){
        tree->left = addNode(tree->left,std);
    }
    else if(tree->std->id < std->id){
        tree->right = addNode(tree->right,std);
    }
    return tree;
}

/**
    @brief Fonction qui recherche un étudiant dans l'arbre grâce à son identifiant
    @param tree L'arbre binaire de recherche contenant les adresses des étudiants
    @param id L'identifiant de l'étudiant à chercher
    @return NULL si l'arbre est vide ou l'étudiant n'a pas été trouvé, ou bien l'adresse de ce dernier s'il a été trouvé
*/
Student* researchNode(pTree tree, int id){
    if(tree==NULL){
        return NULL;
    }
    while(tree!=NULL){
        if(tree->std->id < id){
            tree=tree->right;
        }
        else if(tree->std->id > id){
            tree=tree->left;
        }
        else{
            return tree->std;
        }
    }
    return NULL;
}

/**
    @brief Fonction qui supprime le sous-arbre gauche de l'arbre binaire
    @param tree L'arbre binaire de recherche contenant les adresses des étudiants
*/
void deleteLeft(pTree tree){
    if(tree==NULL || tree->left==NULL){
        return;
    }
    else{
        if(tree->left->left!=NULL){
            deleteLeft(tree->left);
        }
        if(tree->left->right!=NULL){
            deleteRight(tree->left);
        }
        free(tree->left);
        tree->left=NULL;
    }
}

/**
    @brief Fonction qui supprime le sous-arbre droit de l'arbre binaire
    @param tree L'arbre binaire de recherche contenant les adresses des étudiants
*/
void deleteRight(pTree tree){
    if(tree==NULL || tree->right==NULL){
        return;
    }
    else{
        if(tree->right->left!=NULL){
            deleteLeft(tree->right);
        }
        if(tree->right->right!=NULL){
            deleteRight(tree->right);
        }
        free(tree->right);
        tree->right=NULL;
    }
}

/**
    @brief Fonction qui détruit l'arbre binaire de recherche
    @param tree L'arbre binaire de recherche contenant les adresses des étudiants
    @return L'arbre binaire de recherche contenant les adresses des étudiants
*/
pTree destroyTree(pTree tree){
    if(tree!=NULL){
        deleteRight(tree);
        deleteLeft(tree);
        free(tree);
        tree=NULL;
    }
    return tree;
}