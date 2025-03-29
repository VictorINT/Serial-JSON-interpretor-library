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

        // Parse value
        char **str_values = NULL;
        int *int_values = NULL;
        int num_values = 0;

        if (*ptr == '[') {  // Detect array
            ptr++;
            while (*ptr != ']' && *ptr != '\0') {
                while (*ptr == ' ' || *ptr == ',') ptr++;  // Skip whitespace and commas

                if (isdigit(*ptr)) {  // Handle integer values
                    int val = strtol(ptr, &ptr, 10);
                    int_values = realloc(int_values, (num_values + 1) * sizeof(int));
                    int_values[num_values] = val;
                    num_values++;
                }
            }
            if (*ptr == ']') ptr++;  // Skip closing bracket
        } else if (*ptr == '"') {  // Handle string value
            ptr++;
            char *start = ptr;
            while (*ptr != '"' && *ptr != '\0') ptr++;
            if (*ptr == '"') {
                char *value = strndup(start, ptr - start);
                ptr++;

                str_values = malloc(sizeof(char *));
                str_values[0] = value;
                num_values = 1;
            }
        }

        // Store the pair
        if (key) {
            pairs = realloc(pairs, (count + 1) * sizeof(Pair));
            if (pairs == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                return NULL;
            }

            pairs[count].name = key;
            pairs[count].str_values = str_values;
            pairs[count].int_values = int_values;
            pairs[count].num_values = num_values;
            count++;
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
    pairs[count].str_values = NULL;
    pairs[count].int_values = NULL;
    pairs[count].num_values = 0;

    return pairs;
}

void free_pairs(Pair *pairs) {
    for (int i = 0; pairs[i].name != NULL; i++) {
        free(pairs[i].name);
        if (pairs[i].str_values) {
            free(pairs[i].str_values[0]);  // Free the single string
            free(pairs[i].str_values);
        }
        if (pairs[i].int_values) {
            free(pairs[i].int_values);  // Free the int array
        }
    }
    free(pairs);
}