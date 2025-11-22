#ifndef FILES_H
#define FILES_H

#include "data.h"

int recoverData(Class* class, char *filePath);
int saveData(Class* class, char *filePath);
int checkFile(char *path);

#endif