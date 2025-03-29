#ifndef JSONLIB_H
#define JSONLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *name;         // Key name
    char **str_values;  // For string values (NULL if it's an int list)
    int *int_values;    // For integer arrays (NULL if it's a string value)
    int num_values;     // Number of elements in the list
} Pair;

Pair* json_to_pairs(char *json);
void free_pairs(Pair *pairs);

#endif // JSONLIB_H