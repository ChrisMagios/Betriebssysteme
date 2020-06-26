#include <stdio.h>
#include <measure.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_THREADS 16
#define ARRAY_PART 1250

typedef struct{
  bool locked;
}lock_t;

lock_t casLock = {false};
volatile int counter = 0;


void lock(lock_t* lock) {
  if (!(lock->locked)) {
    while(!__sync_bool_compare_and_swap(&(lock->locked), lock->locked, true)) {
    };
    return;
  }
  printf("failed to obtain lock!\n");
  return;
}

void unlock(lock_t *lock) { 
  lock->locked = false;
}


void *counter_inc_lockCas(void* arg) {
  lock(&casLock);
  sleep(2);
  counter++;
  unlock(&casLock);
  return;
}

void *counter_inc_cas(void* arg) {
  int tmp = 0;
  do {
    tmp = counter + 1;
  } while (!__sync_bool_compare_and_swap(&counter, counter, tmp));
  return;
}

int main() {
  pthread_t threads[NUM_THREADS];



  measure_start();

  for (int i = 0; i < NUM_THREADS; i++) {
      printf("MAIN: Creating thread %d.\n", i);
      pthread_create(&threads[i], NULL, counter_inc_lockCas, NULL);
  }

  for (int i = 0; i < NUM_THREADS; i++) {

      pthread_join(threads[i], NULL);
  }


  measure_end();
  measure_print();

  printf("Counter at: %d\n", counter);
  return 0;
}
