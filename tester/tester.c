#include "../serialjson.h"

int led1_function(int *values);
int servo2_function(int *values);
int dc1_function(int *values);
int fan_function(int *values);
int temperature_function(int *values);
int lights_function(int *values);

Item items[] = {
    {"led1", led1_function},
    {"servo2", servo2_function},
    {"DC1", dc1_function},
    {"fan", fan_function},
    {"temperature", temperature_function},
    {"lights", lights_function},
    {NULL, NULL} // Sentinel value to mark the end of the array
};

int main() {
    // Expanded JSON for better testing
    char *json = "{"
        "\"led1\": [1, 2, 3, 4],"
        "\"servo2\": 90,"
        "\"DC1\": 3,"
        "\"temperature\": \"23.5C\","
        "\"humidity\": \"60%\","
        "\"lights\": [0, 1, 1, 0],"
        "\"fan\": \"on\""
    "}";

    Pair *pairs = json_to_pairs(json);
    if (pairs == NULL) {
        fprintf(stderr, "Failed to parse JSON\n");
        return 1;
    }

    for (int i = 0; pairs[i].name != NULL; i++) {
        printf("Key: %s, ", pairs[i].name);

        // Print values (either int array or single string)
        if (pairs[i].int_values) {
            printf("Int Values: ");
            for (int j = 0; j < pairs[i].num_values; j++) {
                printf("%d ", pairs[i].int_values[j]);
            }
        } else if (pairs[i].str_values) {
            printf("String Value: %s", pairs[i].str_values[0]);
        }
        printf("\n");

        // Find corresponding function
        Item item = get_by_name(items, pairs[i].name);
        if (item.name != NULL && pairs[i].int_values) {
            execute_function(item, pairs[i].int_values); // Pass values directly
        } else {
            printf("Item not found or invalid type: %s\n", pairs[i].name);
        }
    }

    free_pairs(pairs); // Free allocated memory
    return 0;
}

// Functions that execute commands based on integer input
int led1_function(int *values) {
    int count = values[0]; // Number of elements is stored in values[0]
    printf("led1: ");
    for (int i = 1; i <= count; i++) { // Start from index 1 since values[0] is count
        printf("%d ", values[i]);
    }
    printf("\n");
    return 0;
}

int servo2_function(int *values) {
    printf("servo2: %d\n", values[1]); // values[0] is count, so we use values[1] for the value
    return 0;
}

int dc1_function(int *values) {
    printf("DC1: %d\n", values[1]); // values[0] is count, so we use values[1] for the value
    return 0;
}

int fan_function(int *values) {
    int count = values[0]; // Number of elements is stored in values[0]
    printf("Fan speed levels: ");
    for (int i = 1; i <= count; i++) { // Start from index 1
        printf("%d ", values[i]);
    }
    printf("\n");
    return 0;
}

int temperature_function(int *values) {
    printf("Temperature sensor raw data: %d\n", values[1]); // values[0] is count, so we use values[1]
    return 0;
}

int lights_function(int *values) {
    int count = values[0]; // Number of elements is stored in values[0]
    printf("Lights states: ");
    for (int i = 1; i <= count; i++) { // Start from index 1
        printf("%d ", values[i]);
    }
    printf("\n");
    return 0;
}
