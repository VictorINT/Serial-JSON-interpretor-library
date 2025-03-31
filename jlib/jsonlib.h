#ifndef JSONLIB_H
#define JSONLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *name;         // Key name
    int *int_values;
    int num_values;     // Number of elements in the list
} Pair;

Pair* json_to_pairs(char *json);
void free_pairs(Pair *pairs);

#endif // JSONLIB_H