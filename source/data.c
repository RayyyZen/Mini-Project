#include "data.h"

/**
    @brief Fonction qui ajoute un étudiant depuis une ligne d'un fichier
    @param class Un pointeur vers la promotion d'étudiants
    @param line Une chaine de caractères contenant une ligne du fichier à traiter
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int addStudent(Class* class, char* line){
    if(class==NULL){
        return 0;
    }
    int id=0,age=0,index=class->size;
    char fname[50],lname[50];
    sscanf(line, "%d;%[^;];%[^;];%d", &id,fname,lname,&age);
    //Le sscanf c'est pour délimiter les champs (séparateur ';') et %[^;] c'est pour dire prend tout jusqu'au ';'
    if(class->capacity == 0){//Premier étudiant ajouté
        class->students=malloc(sizeof(Student));
        if(class->students == NULL){
            return 0;
        }
        class->capacity = 1;
    }
    else if(class->size == class->capacity) {
        class->capacity *= 2;//On multiplie par 2 la capacité du tableau d'étudiants
        class->students = (Student*) realloc(class->students,class->capacity*sizeof(Student));
        //Je ne stocke pas directement l'adresse de l'étudiant dans l'arbre binaire de recherche car les realloc changent les adresses des étudiants et donc les adresses contenues dans l'arbre deviennent erronées
        if(class->students == NULL){
            return 0;
        }
    }

    class->size++;
    class->students[index] = buildStudent();
    class->students[index].id=id;
    class->students[index].age=age;
    class->students[index].sizelname=strlen(lname)+1;
    class->students[index].sizefname=strlen(fname)+1;
    class->students[index].lname=malloc(sizeof(char)*(strlen(lname)+1));
    if(class->students[index].lname==NULL){
        return 0;
    }
    strcpy(class->students[index].lname,lname);
    class->students[index].fname=malloc(sizeof(char)*(strlen(fname)+1));
    if(class->students[index].fname==NULL){
        return 0;
    }
    strcpy(class->students[index].fname,fname);

    return 1;
}

/**
    @brief Fonction qui ajoute une matière depuis une ligne d'un fichier
    @param student Un pointeur vers un étudiant à qui on va mettre toutes les matières du fichier pour en garder une trace sur les coefficients
    @param line Une chaine de caractères contenant une ligne du fichier à traiter
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int addCourse(Student* student, char* line){
    if(student==NULL){
        return 0;
    }
    int index=student->size;
    float coeff=0;
    char name[50];
    sscanf(line, "%[^;];%f", name,&coeff);
    //Le sscanf c'est pour délimiter les champs (séparateur ';') et %[^;] c'est pour dire prend tout jusqu'au ';'
    if(student->capacity == 0){//Première matière ajoutée
        student->courses=malloc(sizeof(Course));
        if(student->courses == NULL){
            return 0;
        }
        student->capacity = 1;
    }
    else if(student->size == student->capacity) {
        student->capacity *= 2;//On multiplie par 2 la capacité du tableau de matières
        student->courses = (Course*) realloc(student->courses,student->capacity*sizeof(Course));
        if(student->courses == NULL){
            return 0;
        }
    }

    student->size++;
    student->courses[index] = buildCourse();
    student->courses[index].coefficient=coeff;
    student->courses[index].sizename=strlen(name)+1;
    student->courses[index].name=malloc(sizeof(char)*(strlen(name)+1));
    if(student->courses[index].name==NULL){
        return 0;
    }
    strcpy(student->courses[index].name,name);

    return 1;
}

/**
    @brief Fonction qui ajoute une note depuis une ligne d'un fichier
    @param class Un pointeur vers la promotion d'étudiants
    @param allcourses Un pointeur vers un étudiant qui contient toutes les matières listées dans le fichier
    @param tree Un arbre binaire de recherche contenant les adresses des étudiants de la promotion
    @param line Une chaine de caractères contenant une ligne du fichier à traiter
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int addGrade(Class* class, Student* allcourses, pTree tree, char* line){
    if(class==NULL){
        return 0;
    }
    int id=0,index=0,i=0,verif=0,k=0;
    float grade=0,sum=0,sumcoeff=0;
    char name[50];
    sscanf(line, "%d;%[^;];%f", &id,name,&grade);
    //Le sscanf c'est pour délimiter les champs (séparateur ';') et %[^;] c'est pour dire prend tout jusqu'au ';'
    Student *std = researchNode(tree,id);
    //Recherche de l'étudiant d'identifiant "id" dans l'arbre binaire de recherche contenant les adresses des étudiants
    if(std == NULL){
        return 0;
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
            if(std->courses==NULL){
                return 0;
            }
            std->capacity = 1;
        }
        else{//Ca veut dire que verif==0 qui veut dire que c'est la première note de l'étudiant dans cette matière
            if(std->capacity == std->size){
                std->capacity *= 2;//On multiplie par 2 la capacité du tableau de matières
                std->courses = (Course*) realloc(std->courses,std->capacity*sizeof(Course));
                if(std->courses==NULL){
                    return 0;
                }
            }
        }
        std->courses[std->size] = buildCourse();
        for(i=0;i<allcourses->size;i++){
            if(strcmp(allcourses->courses[i].name,name) == 0){
                std->courses[std->size].sizename=allcourses->courses[i].sizename;
                std->courses[std->size].name=malloc(sizeof(char)*std->courses[std->size].sizename);
                if(std->courses[std->size].name==NULL){
                    return 0;
                }
                strcpy(std->courses[std->size].name,name);
                std->courses[std->size].coefficient=allcourses->courses[i].coefficient;
                std->courses[std->size].average=grade;

                std->courses[std->size].grades = buildGrades();
                std->courses[std->size].grades.values = malloc(sizeof(float));
                if(std->courses[std->size].grades.values==NULL){
                    return 0;
                }
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
            if(std->courses[index].grades.values==NULL){
                return 0;
            }
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
            if(std->courses[index].grades.values==NULL){
                return 0;
            }
            std->courses[index].grades.values[std->courses[index].grades.size] = grade;
            std->courses[index].grades.size++;
        }
        for(k=0;k<std->size;k++){
            sum += std->courses[k].average*std->courses[k].coefficient;
            sumcoeff += std->courses[k].coefficient;
        }
        std->average = sum/sumcoeff;//Calcul de la moyenne de l'étudiant
    }
    return 1;
}

/**
    @brief Fonction qui retourne l'indice correspondant à une matière
    @param course Un pointeur une matière
    @return L'indice correspondant à la matière passée en paramètre
*/
CourseIndex courseIndex(Course* course){
    if(course == NULL || course->name == NULL){
        return -1;
    }
    else if(!strcmp(course->name,"Mathematiques")){
        return MATHS;
    }
    else if(!strcmp(course->name,"Physique")){
        return PHYSIQUE;
    }
    else if(!strcmp(course->name,"Informatique")){
        return INFORMATIQUE;
    }
    else if(!strcmp(course->name,"Chimie")){
        return CHIMIE;
    }
    else if(!strcmp(course->name,"Biologie")){
        return BIOLOGIE;
    }
    else if(!strcmp(course->name,"Histoire")){
        return HISTOIRE;
    }
    else if(!strcmp(course->name,"Geographie")){
        return GEOGRAPHIE;
    }
    else if(!strcmp(course->name,"Français")){
        return FRANCAIS;
    }
    else if(!strcmp(course->name,"Anglais")){
        return ANGLAIS;
    }
    else if(!strcmp(course->name,"EPS")){
        return EPS;
    }
    else if(!strcmp(course->name,"Philosophie")){
        return PHILOSOPHIE;
    }
    else if(!strcmp(course->name,"Economie")){
        return ECONOMIE;
    }
    else if(!strcmp(course->name,"Sociologie")){
        return SOCIOLOGIE;
    }
    else if(!strcmp(course->name,"Arts Plastiques")){
        return ARTS;
    }
    else if(!strcmp(course->name,"Musique")){
        return MUSIQUE;
    }
    else if(!strcmp(course->name,"Technologie")){
        return TECHNOLOGIE;
    }
    else if(!strcmp(course->name,"Latin")){
        return LATIN;
    }
    else if(!strcmp(course->name,"Espagnol")){
        return ESPAGNOL;
    }
    else if(!strcmp(course->name,"Allemand")){
        return ALLEMAND;
    }
    else if(!strcmp(course->name,"Sciences Sociales")){
        return SOCIALES;
    }
    else{
        return -1;
    }
}

/**
    @brief Fonction qui traite un fichier et remplit une promotion d'étudiants
    @param class Un pointeur vers la promotion d'étudiants
    @param path Une chaine de caractères contenant le chemin du fichier à traiter
    @retval 0 La fonction a rencontré un problème
    @retval 1 La fonction a été exécutée
*/
int dataStorage(Class* class, char* path){
    if(path==NULL || class==NULL){
        return 0;
    }
    class->compare=NULL;

    pTree tree=NULL;
    //L'arbre binaire de recherche qui va stocker les adressesdes étudiants de la promotion
    char line[100];
    char *verif=NULL;
    int i=0,j=0;
    char index=0;
    FILE *file = fopen(path,"r");
    //Ouverture du fichier en lecture
    if(file==NULL){
        return 0;
    }
    Student *allcourses = malloc(sizeof(Student));
    //L'étudiant qui contiendra toutes les matières de la promotion pour garder une trace sur leurs coefficients
    if(allcourses==NULL){
        return 0;
    }
    *allcourses = buildStudent();

    do{
        verif=fgets(line,sizeof(line),file);
    }while(verif!=NULL && strcmp(line,"ETUDIANTS\n")!=0);
    fgets(line,sizeof(line),file);//Pour enlever la ligne juste après "ETUDIANTS"
    while(fgets(line,sizeof(line),file)!=NULL && line[0]!='\n'){
        if(addStudent(class,line)==0){
            return 0;
        }
    }
    class->students = (Student*) realloc(class->students,class->size*sizeof(Student));
    //Pour enlever le surplus de capacité
    if(class->students == NULL){
        return 0;
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
        if(addCourse(allcourses,line)==0){
            return 0;
        }
    }
    allcourses->courses = (Course*) realloc(allcourses->courses,allcourses->size*sizeof(Course));
    //Pour enlever le surplus de capacité
    if(allcourses->courses == NULL){
        return 0;
    }
    allcourses->capacity = allcourses->size;

    do{
        verif=fgets(line,sizeof(line),file);
    }while(verif!=NULL && strcmp(line,"NOTES\n")!=0);
    fgets(line,sizeof(line),file);//Pour enlever la ligne juste après "NOTES"
    while(fgets(line,sizeof(line),file)!=NULL && line[0]!='\n'){
        if(addGrade(class,allcourses,tree,line)==0){
            return 0;
        }
    }
    tree=destroyTree(tree);

    for(i=0;i<class->size;i++){
        class->students[i].courses = (Course*) realloc(class->students[i].courses,class->students[i].size*sizeof(Course));
        if(class->students[i].courses==NULL){
            return 0;
        }
        class->students[i].capacity=class->students[i].size;
        for(j=0;j<class->students[i].size;j++){
            class->students[i].courses[j].grades.values = (float*) realloc(class->students[i].courses[j].grades.values,class->students[i].courses[j].grades.size*sizeof(float));
            if(class->students[i].courses[j].grades.values==NULL){
                return 0;
            }
            class->students[i].courses[j].grades.capacity=class->students[i].courses[j].grades.size;

            index = courseIndex(&class->students[i].courses[j]);
            if(index == -1){//La matière n'existe pas
                return 0;
            }
            if(class->students[i].courses[j].average >= 10.0){
                class->students[i].index |= (1<<index);
                //Mettre la valeur 1 pour le bit qui correspond à la matière que l'étudiant a validé
            }
            else{
                class->students[i].index &= ~(1<<index);
                //Mettre la valeur 0 pour le bit qui correspond à la matière que l'étudiant n'a pas validé
            }
        }
    }
    //Pour enlever le surplus de capacité

    class->size++;
    class->students = (Student*) realloc(class->students,class->size*sizeof(Student));
    if(class->students == NULL){
        return 0;
    }
    class->capacity = class->size;
    class->students[class->size-1]=*allcourses;

    

    fclose(file);
    return 1;
}

/**
    @brief Fonction qui libère toute la mémoire allouée
    @param class Un pointeur vers la promotion d'étudiants
    @return Le pointeur vers la promotion d'étudiants liberé
*/
Class* dataDestroy(Class* class){
    if(class==NULL){
        return class;
    }
    int i=0,j=0;
    if(class->students!=NULL){
        for(i=0;i<class->size;i++){
            if(class->students[i].courses!=NULL){
                for(j=0;j<class->students[i].size;j++){
                    free(class->students[i].courses[j].name);
                    class->students[i].courses[j].name=NULL;
                    destroyGrades(&class->students[i].courses[j].grades);
                }
            }
            free(class->students[i].lname);
            class->students[i].lname=NULL;
            free(class->students[i].fname);
            class->students[i].fname=NULL;
            class->students[i].courses=destroyCourse(class->students[i].courses);
        }
        class->students=destroyStudent(class->students);
    }
    destroyClass(class);
    return class;
}

/**
    @brief Fonction qui crée une clé grâce à une entrée utilisateur utilisée pour chiffrer la vraie clé aléatoire avec laquelle est chiffré le fichier binaire
    @param key Une clé de base initialisée
    @param keySize La taille de la clé
    @retval 1 Le chiffrement de la clé s'est passé avec succés
    @retval 0 Le chiffrement de la clé a échoué
*/
int cipher(unsigned char* key, int keySize){
    if(key==NULL || keySize<=0){
        return 0;
    }
    int verif=0,counter=0;
    char message[50];
    do{
        printf("Entrez un mot de passe d'au moins 16 caractères pour chiffrer le fichier binaire : ");
        verif = scanf("%s",message);
        while(getchar()!='\n'){}
    }while(verif == 0 || strlen(message) < 16);
    while(message[counter]!='\0'){
        key[counter%keySize] ^= (unsigned char)message[counter];
        key[(counter+1)%keySize] += (unsigned char)message[counter];
        key[(counter-1+16)%keySize] *= (unsigned char)message[counter];
        counter++;
    }
    return 1;
}