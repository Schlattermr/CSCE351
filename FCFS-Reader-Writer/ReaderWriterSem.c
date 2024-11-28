#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define INPUT_SIZE 10

sem_t queueSem; // Queue for FCFS Algorithm
sem_t rwSem;
pthread_mutex_t protectingMutex;
int readCount = 0;
int readerId = 1;
int writerId = 1;

void *reader() {
    // Update id for print statement
    pthread_mutex_lock(&protectingMutex);
    int id = readerId++;
    pthread_mutex_unlock(&protectingMutex);

    sem_wait(&queueSem);

    // Enter critial section
    pthread_mutex_lock(&protectingMutex);
    readCount++;
    if (readCount == 1) {
        sem_wait(&rwSem);
    }
    pthread_mutex_unlock(&protectingMutex);
    sem_post(&queueSem);

    // Simulate time elapsing
    printf("Reader %d starts reading\n", id);
    sleep(1);
    printf("Reader %d ends reading\n", id);

    // Exit critical section
    pthread_mutex_lock(&protectingMutex);
    readCount--;
    if (readCount == 0) { // Account for last reader
        sem_post(&rwSem);
    }
    pthread_mutex_unlock(&protectingMutex);

    return NULL;
}

void *writer() {
    // Update id for print statement
    pthread_mutex_lock(&protectingMutex);
    int id = writerId++;
    pthread_mutex_unlock(&protectingMutex);

    // Enter critical section
    sem_wait(&queueSem);
    sem_wait(&rwSem);
    sem_post(&queueSem);

    // Simulate time elapsing
    printf("Writer %d starts writing\n", id);
    sleep(1); 
    printf("Writer %d ends writing\n", id);

    // Exit critical section
    sem_post(&rwSem);

    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != INPUT_SIZE + 1) {
        printf("Error: Include 10 inputs (1's and 0's)\n");
        return 0;
    }

    // Gather and store inputs in an array
    int b[10];
    for(int i = 0; i < INPUT_SIZE; i++) {
        b[i] = atoi(argv[i + 1]);
    }

    // Create semaphores and mutex
    pthread_t threads[INPUT_SIZE];
    sem_init(&queueSem, 0, 1);
    sem_init(&rwSem, 0, 1);
    pthread_mutex_init(&protectingMutex, NULL);

    // Create the ten threads
    for(int i = 0; i < INPUT_SIZE; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;

        if(b[i] == 0) { // reader
            pthread_create(&threads[i], NULL, reader, id);
        } else { // writer
            pthread_create(&threads[i], NULL, writer, id);
        }

        free(id);
    }

    for(int i = 0; i < INPUT_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    sem_destroy(&queueSem);
    sem_destroy(&rwSem);
    pthread_mutex_destroy(&protectingMutex);

    return 0;
}