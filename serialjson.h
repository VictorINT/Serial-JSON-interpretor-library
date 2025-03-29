#ifndef SERIALJSON_H
#define SERIALJSON_H

#include "dfunc/fdex.h"
#include "jlib/jsonlib.h"

/**
 * Declare the functions for each item
 */

int led1_function(int *value);
int servo2_function(int *value);
int dc1_function(int *value);

#endif // SERIALJSON_H