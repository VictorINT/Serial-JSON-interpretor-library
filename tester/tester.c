#include "../serialjson.h"

int main() {
    //! example 1 (usage of function dectionary)
    int *values = (int *)malloc(4 * sizeof(int));
    values[0] = 4; // Count of values
    values[1] = 1; // First value
    values[2] = 2; // Second value
    values[3] = 3; // Third value
    execute_function(get_by_name(ITEMS, "led1"), 4, values); // Test the function directly
    free(values);

    //! example 2 (usage of JSON to function detection)
    char *simplejson = "{\"led1\": [1, 2, 3, 4], \"servo2\": 90, \"DC1\": 3, \"fan\": 1}";

    Pair *pairs = json_to_pairs(simplejson);
    if (pairs == NULL) {
        fprintf(stderr, "Failed to parse JSON\n");
        return 1;
    }

    return 0;
}

// Functions that execute commands based on integer input
int led1_function(int argc, int *argv) {
    printf("led1: ");
    for (int i = 0; i < argc; i++) {
        printf("%d ", argv[i]);
    }
    printf("\n");
    return 0;
}

int servo2_function(int argc, int *argv) {
    printf("servo2: %d\n", argv[0]); 
    return 0;
}

int dc1_function(int argc, int *argv) {
    printf("DC1: %d\n", argv[0]); 
    return 0;
}

int fan_function(int argc, int *argv) {
    printf("Fan speed levels: ");
    for (int i = 0; i < argc; i++) {
        printf("%d ", argv[i]);
    }
    printf("\n");
    return 0;
}

int temperature_function(int argc, int *argv) {
    printf("Temperature sensor raw data: %d\n", argv[0]);
    return 0;
}

int lights_function(int argc, int *argv) {
    printf("Lights states: ");
    for (int i = 0; i < argc; i++) {
        printf("%d ", argv[i]);
    }
    printf("\n");
    return 0;
}
