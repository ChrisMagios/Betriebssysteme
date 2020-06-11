#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

#define NUM_THREADS 16
volatile int counter = 0;
sem_t sem;
pthread_mutex_t mutex;

void *counterInc(){
    for (int i = 0; i < 10000; i++) {
        counter++;
    }
}

void * counterIncSemaphore() {

    sem_wait(&sem);

    for (int i = 0; i < 10000; i++) {
        counter++;
    }

    sem_post(&sem);
}

void * counterIncMutex() {



    for (int i = 0; i < 10000; i++) {

        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }


}


int main() {
    pthread_t threads[NUM_THREADS];
    int retCode;
    retCode = sem_init(&sem, 0, 1);

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("MAIN: Creating thread %d.\n", i);
        int result_code = pthread_create(&threads[i], NULL, counterIncMutex, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("MAIN: Joining thread %d.\n", i);
        int result_code = pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);

    printf("Global Counter Value: %d\n", counter);
}
