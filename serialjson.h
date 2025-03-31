#ifndef SERIALJSON_H
#define SERIALJSON_H

#include "dfunc/fdex.h"
#include "jlib/jsonlib.h"

/**
 * Declare the functions for each item
 */

int led1_function(int argc, int *argv);
int servo2_function(int argc, int *argv);
int dc1_function(int argc, int *argv);
int fan_function(int argc, int *argv);
int temperature_function(int argc, int *argv);
int lights_function(int argc, int *argv);

/**
 * Declare the items with their names and functions
 * The items are used to map the JSON keys to their corresponding functions.
 */

Item ITEMS[] = {
    {"led1", led1_function},
    {"servo2", servo2_function},
    {"DC1", dc1_function},
    {"fan", fan_function},
    {"temperature", temperature_function},
    {"lights", lights_function},
    {NULL, NULL} // Sentinel value to mark the end of the array
};

#endif // SERIALJSON_H