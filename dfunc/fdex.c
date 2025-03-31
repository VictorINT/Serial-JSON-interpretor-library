#include "fdex.h"

int execute_function(Item item, int argc, int *argv) {
    return item.func(argc, argv); // Example value passed to the function
}

Item get_by_name(Item *items, char *name) {
    for (int i = 0; items[i].name != NULL; i++) {
        if (strcmp(items[i].name, name) == 0) {
            return items[i];
        }
    }
    Item not_found = {NULL, NULL}; // Return a sentinel value if not found
    return not_found;
}