#include "data.h"

/**
    @brief Fonction qui ajoute un étudiant depuis une ligne d'un fichier
    @param class Un pointeur vers la promotion d'étudiants
    @param line Une chaine de caractères contenant une ligne du fichier à traiter
*/
void addStudent(Class* class, char* line){
    if(class==NULL){
        exit(0);
    }
    int id=0,age=0,index=class->size;
    char fname[50],lname[50];
    sscanf(line, "%d;%[^;];%[^;];%d", &id,fname,lname,&age);
    //Le sscanf c'est pour délimiter les champs (séparateur ';') et %[^;] c'est pour dire prend tout jusqu'au ';'
    if(class->capacity == 0){//Premier étudiant ajouté
        class->students=malloc(sizeof(Student));
        if(class->students == NULL){
            exit(0);
        }
        class->capacity = 1;
    }
    else if(class->size == class->capacity) {
        class->capacity *= 2;//On multiplie par 2 la capacité du tableau d'étudiants
        class->students = (Student*) realloc(class->students,class->capacity*sizeof(Student));
        //Je ne stocke pas directement l'adresse de l'étudiant dans l'arbre binaire de recherche car les realloc changent les adresses des étudiants et donc les adresses contenues dans l'arbre deviennent erronées
        if(class->students == NULL){
            exit(0);
        }
    }

    class->size++;
    class->students[index] = buildStudent();
    class->students[index].id=id;
    class->students[index].age=age;
    class->students[index].sizelname=strlen(lname)+1;
    class->students[index].sizefname=strlen(fname)+1;
    class->students[index].lname=malloc(sizeof(char)*(strlen(lname)+1));
    strcpy(class->students[index].lname,lname);
    class->students[index].fname=malloc(sizeof(char)*(strlen(fname)+1));
    strcpy(class->students[index].fname,fname);
}

/**
    @brief Fonction qui ajoute une matière depuis une ligne d'un fichier
    @param class Un pointeur vers un étudiant à qui on va mettre toutes les matières du fichier pour en garder une trace sur les coefficients
    @param line Une chaine de caractères contenant une ligne du fichier à traiter
*/
void addCourse(Student* student, char* line){
    if(student==NULL){
        exit(0);
    }
    int index=student->size;
    float coeff=0;
    char name[50];
    sscanf(line, "%[^;];%f", name,&coeff);
    //Le sscanf c'est pour délimiter les champs (séparateur ';') et %[^;] c'est pour dire prend tout jusqu'au ';'
    if(student->capacity == 0){//Première matière ajoutée
        student->courses=malloc(sizeof(Course));
        if(student->courses == NULL){
            exit(0);
        }
        student->capacity = 1;
    }
    else if(student->size == student->capacity) {
        student->capacity *= 2;//On multiplie par 2 la capacité du tableau de matières
        student->courses = (Course*) realloc(student->courses,student->capacity*sizeof(Course));
        if(student->courses == NULL){
            exit(0);
        }
    }

    student->size++;
    student->courses[index] = buildCourse();
    student->courses[index].coefficient=coeff;
    student->courses[index].sizename=strlen(name)+1;
    student->courses[index].name=malloc(sizeof(char)*(strlen(name)+1));
    strcpy(student->courses[index].name,name);
}

/**
    @brief Fonction qui ajoute une note depuis une ligne d'un fichier
    @param class Un pointeur vers la promotion d'étudiants
    @param allcourses Un pointeur vers un étudiant qui contient toutes les matières listées dans le fichier
    @param line Une chaine de caractères contenant une ligne du fichier à traiter
*/
void addGrade(Class* class, Student* allcourses, pTree tree, char* line){
    if(class==NULL){
        exit(0);
    }
    int id=0,index=0,i=0,verif=0,k=0;
    float grade=0,sum=0,sumcoeff=0;
    char name[50];
    sscanf(line, "%d;%[^;];%f", &id,name,&grade);
    //Le sscanf c'est pour délimiter les champs (séparateur ';') et %[^;] c'est pour dire prend tout jusqu'au ';'
    Student *std = researchNode(tree,id);
    //Recherche de l'étudiant d'identifiant "id" dans l'arbre binaire de recherche contenant les adresses des étudiants
    if(std == NULL){
        exit(0);
    }

    for(i=0;i<std->size;i++){
        if(strcmp(std->courses[i].name,name) == 0){//Si l'étudiant a déjà une note dans la matière à laquelle on veut rajouter une note
            index=i;
            verif=1;
            break;
        }
    }

    if(std->capacity==0 || verif==0){
        if(std->capacity==0){//L'étudiant n'a encore aucune matière
            std->courses = malloc(sizeof(Course));
            std->capacity = 1;
        }
        else{//Ca veut dire que verif==0 qui veut dire que c'est la première note de l'étudiant dans cette matière
            if(std->capacity == std->size){
                std->capacity *= 2;//On multiplie par 2 la capacité du tableau de matières
                std->courses = (Course*) realloc(std->courses,std->capacity*sizeof(Course));
            }
        }
        std->courses[std->size] = buildCourse();
        for(i=0;i<allcourses->size;i++){
            if(strcmp(allcourses->courses[i].name,name) == 0){
                std->courses[std->size].sizename=allcourses->courses[i].sizename;
                std->courses[std->size].name=malloc(sizeof(char)*std->courses[std->size].sizename);
                strcpy(std->courses[std->size].name,name);
                std->courses[std->size].coefficient=allcourses->courses[i].coefficient;
                std->courses[std->size].average=grade;

                std->courses[std->size].grades = buildGrades();
                std->courses[std->size].grades.values = malloc(sizeof(float));
                std->courses[std->size].grades.capacity = 1;
                std->courses[std->size].grades.values[std->courses[std->size].grades.size] = grade;
                std->courses[std->size].grades.size++;
            }
        }
        std->size++;
        for(k=0;k<std->size;k++){
            sum += std->courses[k].average*std->courses[k].coefficient;
            sumcoeff += std->courses[k].coefficient;
        }
        std->average = sum/sumcoeff;//Calcul de la moyenne de l'étudiant
    }
    else{//Ce n'est pas la première note de l'étudiant dans cette matière
        std->courses[index].average=((std->courses[index].average*std->courses[index].grades.size)+grade)/(std->courses[index].grades.size+1);
        if(std->courses[index].grades.capacity == 0){//Première note de l'étudiant dans cette matière (On peut enlever ce if car il sera jamais vrai parce que quand il y a une nouvelle note elle est rajoutée en meme temps que sa matière dans le bout de code en haut)
            std->courses[index].grades.values = malloc(sizeof(float));
            std->courses[index].grades.capacity = 1;
            std->courses[index].grades.values[std->courses[index].grades.size] = grade;
            std->courses[index].grades.size++;
        }
        else if(std->courses[index].grades.capacity > std->courses[index].grades.size){//Il y a assez de capacité pour rajouter une note
            std->courses[index].grades.values[std->courses[index].grades.size] = grade;
            std->courses[index].grades.size++;
        }
        else{//Il n y a plus de capacité pour rajouter une note
            std->courses[index].grades.capacity*=2;//On multiplie par 2 la capacité du tableau des notes
            std->courses[index].grades.values = (float*) realloc(std->courses[index].grades.values,std->courses[index].grades.capacity*sizeof(float));
            std->courses[index].grades.values[std->courses[index].grades.size] = grade;
            std->courses[index].grades.size++;
        }
        for(k=0;k<std->size;k++){
            sum += std->courses[k].average*std->courses[k].coefficient;
            sumcoeff += std->courses[k].coefficient;
        }
        std->average = sum/sumcoeff;//Calcul de la moyenne de l'étudiant
    }
}

/**
    @brief Fonction qui traite un fichier et remplit une promotion d'étudiants
    @param class Un pointeur vers la promotion d'étudiants
    @param path Une chaine de caractères contenant le chemin du fichier à traiter
*/
void dataStorage(Class* class, char* path){
    pTree tree=NULL;
    //L'arbre binaire de recherche qui va stocker les adressesdes étudiants de la promotion
    char line[100];
    char *verif=NULL;
    int i=0,j=0;
    FILE *file = fopen(path,"r");
    //Ouverture du fichier en lecture
    if(file==NULL){
        exit(1);
    }
    Student* allcourses = malloc(sizeof(Student));
    //L'étudiant qui contiendra toutes les matières de la promotion pour garder une trace sur leurs coefficients
    if(allcourses==NULL){
        exit(0);
    }
    *allcourses = buildStudent();

    do{
        verif=fgets(line,sizeof(line),file);
    }while(verif!=NULL && strcmp(line,"ETUDIANTS\n")!=0);
    fgets(line,sizeof(line),file);//Pour enlever la ligne juste après "ETUDIANTS"
    while(fgets(line,sizeof(line),file)!=NULL && line[0]!='\n'){
        addStudent(class,line);
    }
    class->students = (Student*) realloc(class->students,class->size*sizeof(Student));
    //Pour enlever le surplus de capacité
    if(class->students == NULL){
        exit(0);
    }
    class->capacity = class->size;

    for(int i=0;i<class->size;i++){
        tree=addNode(tree,&class->students[i]);
        //Remplissage du tableau binaire de recherche avec les adresses des étudiants de la promotion
    }

    do{
        verif=fgets(line,sizeof(line),file);
    }while(verif!=NULL && strcmp(line,"MATIERES\n")!=0);
    fgets(line,sizeof(line),file);//Pour enlever la ligne juste après "MATIERES"
    while(fgets(line,sizeof(line),file)!=NULL && line[0]!='\n'){
        addCourse(allcourses,line);
    }
    allcourses->courses = (Course*) realloc(allcourses->courses,allcourses->size*sizeof(Course));
    //Pour enlever le surplus de capacité
    if(allcourses->courses == NULL){
        exit(0);
    }
    allcourses->capacity = allcourses->size;


    do{
        verif=fgets(line,sizeof(line),file);
    }while(verif!=NULL && strcmp(line,"NOTES\n")!=0);
    fgets(line,sizeof(line),file);//Pour enlever la ligne juste après "NOTES"
    while(fgets(line,sizeof(line),file)!=NULL && line[0]!='\n'){
        addGrade(class,allcourses,tree,line);
    }
    tree=destroyTree(tree);

    for(i=0;i<class->size;i++){
        class->students[i].courses = (Course*) realloc(class->students[i].courses,class->students[i].size*sizeof(Course));
        if(class->students[i].courses==NULL){
            exit(0);
        }
        class->students[i].capacity=class->students[i].size;
        for(j=0;j<class->students[i].size;j++){
            class->students[i].courses[j].grades.values = (float*) realloc(class->students[i].courses[j].grades.values,class->students[i].courses[j].grades.size*sizeof(float));
            if(class->students[i].courses[j].grades.values==NULL){
                exit(0);
            }
            class->students[i].courses[j].grades.capacity=class->students[i].courses[j].grades.size;
        }
    }
    //Pour enlever le surplus de capacité

    fclose(file);
}