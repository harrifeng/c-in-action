#include <pthread.h>
#include <stdio.h>

int avail = 0;
void *
reader(void* arg) {
    int i = 0;
    for (i = 0; i < 3000; i++) {
        avail++;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int s = 0;
    int i = 0;
    pthread_t t1, t2;
    s = pthread_create(&t1, NULL, &reader, NULL);
    s = pthread_create(&t2, NULL, &reader, NULL);

    if (s != 0) {
        printf("Error in pthread_create");
    }

    for (i = 0; i < 100000; i++) {

    }

    printf("avail is %d\n", avail);
    return 0;
}

/**************************************************/
/* <===================OUTPUT===================> */
/* $ gcc unsafe.c -pthread                        */
/* $ ./a.out                                      */
/* avail is 5731                                  */
/**************************************************/
