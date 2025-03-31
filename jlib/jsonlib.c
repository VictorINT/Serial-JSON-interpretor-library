#include "jsonlib.h"

Pair* json_to_pairs(char *json) {
    Pair *pairs = malloc(sizeof(Pair)); // Initial allocation
    if (pairs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    int count = 0; // Number of pairs
    char *key = NULL;
    char *ptr = json;

    while (*ptr) {
        // Skip whitespace and commas
        while (*ptr == ' ' || *ptr == ',' || *ptr == '{' || *ptr == '}') {
            ptr++;
        }

        if (*ptr == '\0') break; // Exit if we reach the end

        // Parse key
        if (*ptr == '"') {
            ptr++;
            char *start = ptr;
            while (*ptr != '"' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == '"') {
                key = strndup(start, ptr - start);
                ptr++;
            }
        }

        // Skip whitespace and colon
        while (*ptr == ' ' || *ptr == ':') {
            ptr++;
        }

        // Parse value (integers only)
        int *int_values = NULL;
        int num_values = 0;

        if (*ptr == '[') {  // Detect array
            ptr++;
            while (*ptr != ']' && *ptr != '\0') {
                while (*ptr == ' ' || *ptr == ',') ptr++;  // Skip whitespace and commas

                if (*ptr == ']') break; // Check for empty array or end of array

                if (isdigit(*ptr) || *ptr == '-') {  // Handle integer values
                    char *end;
                    int val = strtol(ptr, &end, 10);
                    if (end != ptr) { // Make sure we actually parsed a number
                        ptr = end; // Update pointer position
                        int_values = realloc(int_values, (num_values + 1) * sizeof(int));
                        if (int_values == NULL) {
                            fprintf(stderr, "Memory reallocation failed\n");
                            free(key);
                            return NULL;
                        }
                        int_values[num_values] = val;
                        num_values++;
                    } else {
                        ptr++; // Avoid infinite loop
                    }
                } else {
                    ptr++; // Skip any other characters to avoid infinite loop
                }
            }
            if (*ptr == ']') ptr++;  // Skip closing bracket
        } else if (isdigit(*ptr) || *ptr == '-') {  // Handle single numeric value
            char *end;
            int val = strtol(ptr, &end, 10);
            if (end != ptr) { // Make sure we actually parsed a number
                ptr = end; // Update pointer position
                int_values = malloc(sizeof(int));
                if (int_values == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(key);
                    return NULL;
                }
                int_values[0] = val;
                num_values = 1;
            } else {
                ptr++; // Avoid infinite loop
            }
        } else {
            // Skip non-integer values
            while (*ptr != ',' && *ptr != '}' && *ptr != '\0') ptr++;
        }

        // Store the pair if we have a key and values
        if (key && num_values > 0) {
            pairs = realloc(pairs, (count + 1) * sizeof(Pair));
            if (pairs == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(key);
                free(int_values);
                return NULL;
            }
            pairs[count].name = key;
            pairs[count].int_values = int_values;
            pairs[count].num_values = num_values;
            
            // Safe printing
            puts("Pair added:");
            // puts(pairs[count].name);
            for (int i = 0; i < num_values; i++) {
                printf("%d ", pairs[count].int_values[i]);
            }
            printf("\n");
            
            count++;
            key = NULL;
        } else if (key) {
            // Free the key if we didn't find any values for it
            free(key);
            key = NULL;
        }
    }

    // Add a NULL terminator pair
    pairs = realloc(pairs, (count + 1) * sizeof(Pair));
    if (pairs == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        return NULL;
    }
    pairs[count].name = NULL;
    pairs[count].int_values = NULL;
    pairs[count].num_values = 0;

    return pairs;
}

void free_pairs(Pair *pairs) {
    for (int i = 0; pairs[i].name != NULL; i++) {
        free(pairs[i].name);
        if (pairs[i].int_values) {
            free(pairs[i].int_values);  // Free the int array
        }
    }
    free(pairs);
}