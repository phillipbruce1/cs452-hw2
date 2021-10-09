#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include "mtq.h"

typedef struct Params {
    Deq q;
    Lawn lawn;
} Params;

static void *produce(void *a) {
    Params *p;
    p = (Params *) a;
    Params t = *p;
    Deq q = t.q;
    Lawn l = t.lawn;
    mtq_tail_put(q, mole_new(l, 0, 0));
    return 0;
}

static void *consume(void *a) {
    Params *p;
    p = (Params *) a;
    Params t = *p;
    Deq q = t.q;
    mole_whack(mtq_head_get(q));
    return 0;
}

static void create_threads(pthread_t *threads, void* params, int n) {
    for (int i = 0; i < n * 2;) {
        pthread_create(&threads[i++], 0, produce, (void *) params);
        pthread_create(&threads[i++], 0, consume, (void *) params);
    }
}

static void join_threads(pthread_t *threads, void* params, int n) {
    for (int i = 0; i < n * 2;) {
        pthread_join(threads[i++], 0);
        pthread_join(threads[i++], 0);
    }
}

int main() {
    srandom(time(0));
    // initialize vars
    int n = 100;
    Deq q = deq_new();
    Lawn lawn = lawn_new(0, 0);
    // initialize params
    Params *params;
    params = (Params *) malloc(sizeof(Params));
    params->q = q;
    params->lawn = lawn;
    // create threads
    pthread_t threads[n * 2];
    create_threads(threads, params, n);
    // join threads
    join_threads(threads, params, n);
    // free vars
    free(params);
    free_mtq();
    lawn_free(lawn);
    deq_del(q, 0);
}
