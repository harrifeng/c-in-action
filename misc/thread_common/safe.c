#include <pthread.h>
#include <stdio.h>

int avail = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void*
producer(void* arg) {
    int i = 0;
    int s = 0;
    for (i = 0; i < 1000000; i++) {
    }

    s = pthread_mutex_lock(&mtx);
    for (i = 0; i < 3000; i++) {
        avail++;
    }
    s = pthread_mutex_unlock(&mtx);
    s = pthread_cond_signal(&cond);

    return NULL;
}

int main(int argc, char *argv[])
{
    int s = 0;
    int i = 0;
    pthread_t t1, t2;

    s = pthread_create(&t1, NULL, &producer, NULL);
    s = pthread_create(&t2, NULL, &producer, NULL);

    s = pthread_mutex_lock(&mtx);

    while (avail < 6000) {
        s = pthread_cond_wait(&cond, &mtx);
        printf("In the loop, Now avail number is %d\n", avail);
    }

    printf("Now avail number is %d\n", avail);
    s = pthread_mutex_unlock(&mtx);
    return 0;
}

/**************************************************/
/* <===================OUTPUT===================> */
/* ./a.out                                        */
/* In the loop, Now avail number is 3000          */
/* In the loop, Now avail number is 6000          */
/* Now avail number is 6000                       */
/**************************************************/
