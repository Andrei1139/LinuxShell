#include <stdlib.h>
#include "shell.h"

int main() {
    clear();

    char *line = malloc(MAX_LEN * sizeof(char));
    if (line == NULL) {
        fprintf(stderr, "Couldn't allocate memory\n");
        return -1;
    }

    size_t result;

    while (1) {
        printf("> ");
        result = getline(&line, &result, stdin);
        if (result == -1) {
            fprintf(stderr, "Entering input failed\n");
            free(line);
            exit(-1);
        }

        if (line[0] == '\n')
            continue;

        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
            
        process_input(line);
    }
    
    free(line);
    return 0;
}