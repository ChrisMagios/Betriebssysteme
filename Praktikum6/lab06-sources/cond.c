#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#define NUM_THREADS 128

int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* counter() {
  pthread_mutex_lock( &mutex );
  count++;
  pthread_cond_signal( &cond ); 
  pthread_mutex_unlock( & mutex );
  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];
  for( int t = 0; t < NUM_THREADS; t++ )
    pthread_create( &threads[t], NULL, counter, NULL );
  pthread_mutex_lock( &mutex );
  while( count < NUM_THREADS )
    pthread_cond_wait( & cond, & mutex ); 

  pthread_mutex_unlock( & mutex );
  return 0;
}