#include <stdio.h>
#include <measure.h>
#include <pthread.h>

#define NUM_THREADS 8
#define ARRAY_PART 1250


extern int A[];
volatile int x = 0;
pthread_mutex_t mutex;


void *sum_array(void* arg) {

  int offset = *((int*) arg);

  for ( int i = ARRAY_PART * offset; i < ((offset + 1) * ARRAY_PART); i ++) {
    pthread_mutex_lock(&mutex);
    x += A[i] ;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *sum_array_whithout_lock(void* arg) {

  int offset = *((int*) arg);
  int part_sum = 0;
  for ( int i = ARRAY_PART * offset; i < ((offset + 1) * ARRAY_PART); i ++) {

    part_sum += A[i] ;

  }
  return (void *) part_sum;
}

int main() {

  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int part_sum[NUM_THREADS];
  int sum = 0;
  pthread_mutex_init(&mutex, NULL);
  measure_start();

  for (int i = 0; i < NUM_THREADS; i++) {
      printf("MAIN: Creating thread %d.\n", i);
      thread_args[i] = i;
      pthread_create(&threads[i], NULL, sum_array_whithout_lock,(void *) &thread_args[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {

      pthread_join(threads[i],(void *) &part_sum[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {

      sum += part_sum[i];
  }

  measure_end();
  measure_print();

  printf("Ergebniss: %d\n", sum);
  return 0;
}
