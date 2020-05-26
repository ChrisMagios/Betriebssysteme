#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *read_thread_id (void *i)
{
    printf ("Thread-Id: %ld\n", pthread_self());
    printf ("Arg: %d\n", *(int*) i);
    return NULL;
}

int main ()
{
    pthread_t t1, t2, t3, t4;
    int arg1 = 1, arg2 = 2, arg3 = 3;
    pthread_create(&t1, NULL, read_thread_id, &arg1);
    pthread_create(&t2, NULL, read_thread_id, &arg2);
    pthread_create(&t3, NULL, read_thread_id, &arg3);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_create(&t4, NULL, read_thread_id, &arg1);
    pthread_detach(t4);
    sleep(20);

    return 0;
}