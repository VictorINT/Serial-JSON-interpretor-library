#include "../serialjson.h"

int main() {
    //! example file
    char *json = "{\"led1\": [1, 2, 3, 4], \"servo2\": 90, \"DC1\": 3, \"fan\": 1}";

    Pair *pairs = json_to_pairs(json);
    if (pairs == NULL) {
        fprintf(stderr, "Failed to parse JSON\n");
        return 1;
    }

    int index = 0;
    while(pairs[index].name != NULL){
        execute_function(get_by_name(ITEMS, pairs[index].name), pairs[index].num_values, pairs[index].int_values);
        index++;
    }

    free_pairs(pairs); // Free the pairs after use
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
