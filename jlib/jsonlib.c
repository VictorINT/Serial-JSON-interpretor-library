#include "jsonlib.h"

Pair* json_to_pairs(char *json) {
    // printf("Starting JSON parsing\n");
    
    Pair *pairs = malloc(sizeof(Pair)); // Initial allocation
    if (pairs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    memset(pairs, 0, sizeof(Pair)); // Initialize memory to zero
    
    int count = 0; // Number of pairs
    char *key = NULL;
    char *ptr = json;

    // printf("JSON to parse: %s\n", json);

    while (*ptr) {
        // printf("Processing at position: %ld ('%c')\n", (long)(ptr - json), *ptr);
        
        // Skip whitespace and commas
        while (*ptr == ' ' || *ptr == ',' || *ptr == '{' || *ptr == '}') {
            ptr++;
        }

        if (*ptr == '\0') {
            // printf("End of string reached\n");
            break;
        }

        // Parse key
        if (*ptr == '"') {
            ptr++;
            char *start = ptr;
            while (*ptr != '"' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == '"') {
                int key_len = ptr - start;
                // printf("Found key of length %d: ", key_len);
                // for (int i = 0; i < key_len; i++) {
                //     printf("%c", start[i]);
                // }
                // printf("\n");
                
                // Manual string duplication instead of strndup
                key = malloc(key_len + 1);
                if (key == NULL) {
                    fprintf(stderr, "Failed to allocate memory for key\n");
                    // Clean up and return error
                    for (int i = 0; i < count; i++) {
                        free(pairs[i].name);
                        free(pairs[i].int_values);
                    }
                    free(pairs);
                    return NULL;
                }
                memcpy(key, start, key_len);
                key[key_len] = '\0';  // Null-terminate the string
                
                // printf("Key allocated: %s\n", key);
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
            // printf("Found array start\n");
            ptr++;
            while (*ptr != ']' && *ptr != '\0') {
                while (*ptr == ' ' || *ptr == ',') ptr++;  // Skip whitespace and commas

                if (*ptr == ']') break; // Check for empty array or end of array

                if (isdigit(*ptr) || *ptr == '-') {  // Handle integer values
                    char *end;
                    int val = strtol(ptr, &end, 10);
                    if (end != ptr) { // Make sure we actually parsed a number
                        // printf("Found integer: %d\n", val);
                        ptr = end; // Update pointer position
                        
                        // Safer realloc pattern
                        int *new_values = realloc(int_values, (num_values + 1) * sizeof(int));
                        if (new_values == NULL) {
                            fprintf(stderr, "Memory reallocation failed\n");
                            free(key);
                            free(int_values);
                            for (int i = 0; i < count; i++) {
                                free(pairs[i].name);
                                free(pairs[i].int_values);
                            }
                            free(pairs);
                            return NULL;
                        }
                        int_values = new_values;
                        int_values[num_values] = val;
                        num_values++;
                    } else {
                        ptr++; // Avoid infinite loop
                    }
                } else {
                    ptr++; // Skip any other characters to avoid infinite loop
                }
            }
            if (*ptr == ']') {
                // printf("Found array end, total values: %d\n", num_values);
                ptr++;  // Skip closing bracket
            }
        } else if (isdigit(*ptr) || *ptr == '-') {  // Handle single numeric value
            char *end;
            int val = strtol(ptr, &end, 10);
            if (end != ptr) { // Make sure we actually parsed a number
                // printf("Found single integer: %d\n", val);
                ptr = end; // Update pointer position
                int_values = malloc(sizeof(int));
                if (int_values == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(key);
                    for (int i = 0; i < count; i++) {
                        free(pairs[i].name);
                        free(pairs[i].int_values);
                    }
                    free(pairs);
                    return NULL;
                }
                int_values[0] = val;
                num_values = 1;
            } else {
                ptr++; // Avoid infinite loop
            }
        } else {
            // Skip non-integer values
            // printf("Skipping non-integer value\n");
            while (*ptr != ',' && *ptr != '}' && *ptr != '\0') ptr++;
        }

        // Store the pair if we have a key and values
        if (key != NULL && num_values > 0) {
            // printf("Storing pair: %s with %d values\n", key, num_values);
            
            // Safe realloc pattern
            Pair *new_pairs = realloc(pairs, (count + 1) * sizeof(Pair));
            if (new_pairs == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(key);
                free(int_values);
                for (int i = 0; i < count; i++) {
                    free(pairs[i].name);
                    free(pairs[i].int_values);
                }
                free(pairs);
                return NULL;
            }
            pairs = new_pairs;
            
            pairs[count].name = key;
            pairs[count].int_values = int_values;
            pairs[count].num_values = num_values;
            
            //! testing
            // printf("Added pair with key: %s (ptr: %p)\n", key, (void*)key);
            // for(int i = 0; i < num_values; i++) {
            //     printf("Value %d: %d\n", i, int_values[i]);
            // }

            count++;
            key = NULL;
        } else if (key != NULL) {
            // Free the key if we didn't find any values for it
            // printf("No values found for key: %s, freeing\n", key);
            free(key);
            key = NULL;
        }
    }

    // Add a NULL terminator pair
    // printf("Adding terminator, total pairs: %d\n", count);
    Pair *new_pairs = realloc(pairs, (count + 1) * sizeof(Pair));
    if (new_pairs == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        for (int i = 0; i < count; i++) {
            free(pairs[i].name);
            free(pairs[i].int_values);
        }
        free(pairs);
        return NULL;
    }
    pairs = new_pairs;
    
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