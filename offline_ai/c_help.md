#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populateArrays(const char *input, char ***names, double **values, int *numPairs) {
    // Count the number of pairs
    *numPairs = 0;
    const char *ptr = input;
    while (*ptr != '\0') {
        if (*ptr == ':')
            (*numPairs)++;
        ptr++;
    }
    *numPairs /= 2; // Since each pair contains a name and a value
    
    // Allocate memory for names and values arrays
    *names = (char **)malloc(*numPairs * sizeof(char *));
    *values = (double *)malloc(*numPairs * sizeof(double));
    
    // Parse the input string
    char *token = strtok((char *)input, ":");
    int index = 0;
    while (token != NULL) {
        (*names)[index] = strdup(token); // Allocate memory for each name and copy
        token = strtok(NULL, ":");
        (*values)[index] = atof(token); // Convert string to double
        token = strtok(NULL, ":");
        index++;
    }
}

int main() {
    const char *input = "A:2.0:BB:3.0:ABD:4.0";
    char **names;
    double *values;
    int numPairs;

    populateArrays(input, &names, &values, &numPairs);

    // Print the populated arrays
    printf("Populated arrays:\n");
    for (int i = 0; i < numPairs; i++) {
        printf("Name: %s, Value: %.1f\n", names[i], values[i]);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < numPairs; i++) {
        free(names[i]);
    }
    free(names);
    free(values);

    return 0;
}