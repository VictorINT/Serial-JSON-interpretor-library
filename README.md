# Serial JSON Interpreter Library

A lightweight C library for parsing and interpreting JSON data received over serial communication. Designed for ARM microcontrollers, but easily adaptable to any low-level embedded platform that supports C and serial interfaces.

## Features

- Efficient JSON parsing for resource-constrained environments
- Seamless integration with serial communication
- Written in portable C for easy adaptation to various microcontrollers
- Simple API for extracting values from JSON objects

## Note on Memory Management

This library currently relies on dynamic memory allocation, which may introduce certain risks such as fragmentation or allocation failures, especially on resource-constrained embedded systems. Please keep this in mind when integrating the library into your project.

I am actively working on an alternative implementation that utilizes object pools for safer and more predictable memory management. This version will be released soon in a separate branch.

## Installation

1. **Clone or Download the Repository**
   ```sh
   git clone https://github.com/VictorINT/Serial-JSON-interpretor-library.git
   ```
2. **Copy the Library**
   - Place the library folder into your project or your platform's library directory.
3. **Include the Header**
   - In your source file, include the main header:
     ```c
     #include "serialjson.h"
     ```

## Example Usage

Below is a minimal example for an ARM microcontroller using a serial interface (adaptable for any low-level MCU):

```c
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
```
