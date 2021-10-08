#include <pthread.h>

#include "mtq.h"
#include "lawn.h"
#include "deq.h"

static pthread_mutex_t mutex;

extern void init_mutex() {
    pthread_mutex_init(&mutex, 0);
    return 0;
}

extern void create_n_threads(int n, void *function, void *params) {
    for (int i = 0; i < n; i++)
        pthread_create(i, 0, function, params);
}

extern void mtq_tail_put(Mtq q, Mole m) {
    pthread_mutex_lock(&mutex);
    Data d = &m;
    deq_tail_put((Deq*) q, d);
    pthread_mutex_unlock(&mutex);
}