#include <pthread.h>

/* types */
typedef struct {
  pthread_cond_t     cond;	      /* cv for waiters at barrier */
  pthread_mutex_t    lock;	      /* mutex for waiters at barrier */
  int	             maxcnt;          /* number of threads to wait for */
  int                cnt;             /* number of waiting threads */
  int                phase;           /* flag to seperate two barriers */
} barrier_t;

void barrier_init( barrier_t *b, int N);
void barrier(barrier_t *bp);