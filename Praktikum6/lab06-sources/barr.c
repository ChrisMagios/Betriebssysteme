#include "barr.h"

void barrier_init( barrier_t *b, int N) {
  b->maxcnt = N;
  b->cnt    = 0;
  b->phase  = 0;
  pthread_mutex_init(&b->lock, NULL);
  pthread_cond_init(&b->cond, NULL);
}

void barrier(barrier_t *bp) {
  int my_phase;

  pthread_mutex_lock(&bp->lock);
  my_phase = bp->phase;
  bp->cnt++;

  if (bp->cnt == bp->maxcnt) {
    bp->cnt = 0;
    bp->phase = 1 - my_phase;
    pthread_cond_broadcast(&bp->cond);
  } 
  while (bp->phase == my_phase) {
    pthread_cond_wait(&bp->cond, &bp->lock);
  }
  pthread_mutex_unlock(&bp->lock);
}
