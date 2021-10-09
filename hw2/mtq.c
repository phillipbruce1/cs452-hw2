#include <pthread.h>
#include <stdio.h>

#include "mtq.h"
#include "lawn.h"
#include "deq.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t onPut = PTHREAD_COND_INITIALIZER;
pthread_cond_t onGet = PTHREAD_COND_INITIALIZER;

/**
 * Adds a new Mole onto the tail of the Deq, only when no other threads are using it.
 * @param q - Deq containing Moles
 * @param d - Data (Mole) to add to Deq
 */
extern void mtq_tail_put(Deq q, Data d) {
    pthread_mutex_lock(&mutex);
    deq_tail_put(q, d);
    pthread_cond_signal(&onPut);
    pthread_mutex_unlock(&mutex);
}

/**
 * Removes a Mole from the head of the Deq and returns it, only when no other threads are using it
 * @param q - Deq containing Mole to be removed
 * @return - Mole removed
 */
extern Data mtq_head_get(Deq q) {
    pthread_mutex_lock(&mutex);
    while (deq_len(q) == 0)
        pthread_cond_wait(&onPut, &mutex);
    Data d = deq_head_get(q);
    pthread_cond_signal(&onGet);
    pthread_mutex_unlock(&mutex);
    return d;
}

/**
 * Frees the thread locks
 */
extern void free_mtq() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&onPut);
    pthread_cond_destroy(&onGet);
}