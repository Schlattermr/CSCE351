#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *reader() {
    return NULL;
}

void *writer() {
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 11) {
        printf("Error: Include 10 inputs (1's and 0's)");
    }

    // Gather and store inputs in an array
    int b[10];
    for(int i = 0; i < argc; i++) {
        b[i] = atoi(argv[i + 1]);
    }

    int arrayLength = sizeof(b) / sizeof(b[0]);
    pthread_t threads[arrayLength];

    // Create the ten threads
    for(int i = 0; i < arrayLength; i++) {
        if(b[i] == 0) { // reader
            printf("Reader %d starts reading", i + 1);

            pthread_create(&threads[i], NULL, &reader, NULL);

            printf("Reader %d ends reading", i + 1);
        } else { // writer
            printf("Writer %d starts writing", i + 1);

            pthread_create(&threads[i], NULL, &writer, NULL);

            printf("Writer %d ends writing", i + 1);
        }
    }
}