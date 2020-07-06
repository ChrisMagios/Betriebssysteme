#include "barr.h"
#include <stdio.h>
#include <unistd.h>

barrier_t b;
extern int A[];
int x = 0;

void *thread1()
{
    printf ("thread1 starting");
    for (int i = 0; i < 10000; i++) {
        x += A[i]; 
    }
    barrier(&b);
    printf ("barrier in thread1() done");
}

void *thread2() {
    printf ("thread2 starting");
    x /= 100;
    for (int i = 0; i < 10000; i++) {
        A[i] = A[i] * x;
    }
    barrier(&b);
    printf("barrier done");
}

int main() {
    pthread_t t1, t2;
    barrier_init(&b,3);
    pthread_create (&t1, NULL, thread1, NULL);
    pthread_create (&t2, NULL, thread2, NULL);

    barrier(&b);
    return 0;
} 