#ifndef FDEX_H
#define FDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int (*Function)(int, int*);

struct item{ 
    char *name;
    Function func;
};

typedef struct item Item;
// Function declarations
int execute_function(Item item,int argc, int *argv);
Item get_by_name(Item *items, char *name);

#endif // FDEX_H
