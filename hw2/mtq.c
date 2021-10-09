#include <pthread.h>
#include <stdio.h>

#include "mtq.h"
#include "lawn.h"
#include "deq.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t onPut = PTHREAD_COND_INITIALIZER;
pthread_cond_t onGet = PTHREAD_COND_INITIALIZER;

extern void mtq_tail_put(Deq q, Data d) {
    printf("Put before lock\n");
    pthread_mutex_lock(&mutex);
    printf("Putting\n");
    deq_tail_put(q, d);
    printf("Put completed\n");
    printf("Put. New length: %d\n", deq_len(q));
    pthread_cond_signal(&onPut);
    pthread_mutex_unlock(&mutex);
    printf("Put unlocked\n");
}

extern Data mtq_head_get(Deq q) {
    printf("Get head before lock\n");
    pthread_mutex_lock(&mutex);
    printf("Get head locked\n");
    while (deq_len(q) == 0) {
        printf("%d\n", deq_len(q));
        pthread_cond_wait(&onPut, &mutex);
        printf("Still waiting");
    }
    printf("Time to get head\n");
    Data d = deq_head_get(q);
    pthread_cond_signal(&onGet);
    pthread_mutex_unlock(&mutex);
    printf("Get head unlocked\n");
    return d;
}

extern void free_mtq() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&onPut);
    pthread_cond_destroy(&onGet);
}