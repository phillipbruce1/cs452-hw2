#include <pthread.h>
#include <stdio.h>

#include "mtq.h"
#include "lawn.h"
#include "deq.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t onPut = PTHREAD_COND_INITIALIZER;
pthread_cond_t onGet = PTHREAD_COND_INITIALIZER;

extern void mtq_tail_put(Deq q, Data d) {
    pthread_mutex_lock(&mutex);
    deq_tail_put(q, d);
    pthread_cond_signal(&onPut);
    pthread_mutex_unlock(&mutex);
}

extern Data mtq_head_get(Deq q) {
    pthread_mutex_lock(&mutex);
    printf("Get head locked");
    while (deq_len(q) == 0)
        pthread_cond_wait(&onPut, &mutex);
    Data d = deq_head_get(q);
    pthread_cond_signal(&onGet);
    pthread_mutex_unlock(&mutex);
    printf("Get head unlocked");
    return d;
}

extern void free_mtq() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&onPut);
    pthread_cond_destroy(&onGet);
}