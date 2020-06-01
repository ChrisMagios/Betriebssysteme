#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NTHREADS 4
#define ARRAYSIZE 1000

void *count(void *x)
{
    int tid = *((int *) x);
    int j = tid * (ARRAYSIZE/NTHREADS);
    int* buffer = malloc((ARRAYSIZE/NTHREADS) * sizeof(*buffer));

    for (int i = 0; i<ARRAYSIZE/NTHREADS; i++) {
        buffer[i] = j*2;
        printf("buffer: %d\n", buffer[i]);
        j++;
    }
    return buffer;
}

int main() {
    pthread_t threads[NTHREADS];
    int thread_args[NTHREADS];
    int* A = malloc(ARRAYSIZE * sizeof(int));
    int i;
    void *answer;

    /* spawn the threads */
    for (i=0; i<NTHREADS; ++i)
        {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, count, (void *) &thread_args[i]);
        }

    /* wait for threads to finish */
    for (i=0; i<NTHREADS; ++i) {
        pthread_join(threads[i], &answer);
        memcpy(A+(i*ARRAYSIZE/NTHREADS),answer,(ARRAYSIZE/NTHREADS)*sizeof(int));
    }

    printf("Result\n");
    for(i=0;i<ARRAYSIZE; i++) {
        printf("%d\n", A[i]);
    }
    return 0;
};