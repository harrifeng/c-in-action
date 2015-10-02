#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int totThreads = 0;      /* Totoal number of threads created */
static int numLive = 0;         /* Total number of threads still alive
                                   or terminated but not yet joined*/

static int numUnJoined = 0;     /* Number of terminated threads that
                                   have not yet been joined*/

enum tstate {
    TS_ALIVE,
    TS_TERMINATED,
    TS_JOINED
};


static struct {
    pthread_t tid;
    enum tstate state;
    int sleepTime;
} *thread;

static void*
threadFunc(void *arg) {
    int idx = *((int*)arg);
    int s;
    sleep(thread[idx].sleepTime);
    printf("Thread %d terminating\n", idx);

    s = pthread_mutex_lock(&threadMutex);
    if (s != 0) {
        printf("pthread_mutex_lock error");
    }

    numUnJoined++;
    thread[idx].state = TS_TERMINATED;

    s = pthread_mutex_unlock(&threadMutex);

    if (s != 0) {
        printf("pthread_mutex_unlock error");
    }
    s = pthread_cond_signal(&threadDied);
    if (s != 0) {
        printf("pthread_cond_signal error");
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int s, idx;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("Wrong argument");
    }

    thread = calloc(argc - 1, sizeof(*thread));
    if (thread == NULL) {
        printf("calloc error");
    }

    /* Create all threads */

    for (idx = 0; idx < argc - 1; idx++) {
        thread[idx].sleepTime = getInt(argv[idx+1], GN_NONNEG, NULL);
        thread[idx].state = TS_ALIVE;
        s = pthread_create(&thread[idx].tid, NULL, threadFunc, &idx);
        if (s != 0) {
            printf("pthread_create error");
        }
    }

    totThreads = argc - 1;
    numLive = totThreads;

    /* Join with terminated threads */

    while (numLive > 0) {
        s = pthread_mutex_lock(&threadMutex);
        if (s != 0) {
            printf("error");
        }
        while (numUnJoined == 0) {
            s = pthread_cond_wait(&threadDied, &threadMutex);
            if (s != 0) {
                printf("error");
            }
        }
        for (idx = 0; idx < totThreads; idx++) {
            if (thread[idx].state == TS_TERMINATED) {
                s = pthread_join(thread[idx].tid, NULL);
                if (s != 0) {
                    printf("error");
                }

                thread[idx].state = TS_JOINED;
                numLive--;
                numUnJoined--;

                printf("Reaped thread %d (numLive=%d)", idx, numLive);
            }
        }

        s = pthread_mutex_unlock(&threadMutex);
        if (s != 0) {
            printf("error");
        }
    }
    return 0;
}
