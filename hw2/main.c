#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "libdeq.h"
#include "mtq.h"

typedef struct Params {
    Deq q;
    Lawn lawn;
} Params;

static void* produce(void *a) {
    Params *p;
    p = (Params *) a;
    Deq q = (Deq) p->q;
    Lawn l = (Lawn) p->lawn;
    Data *d = (Data *) mole_new(l, 0, 0);
    mtq_tail_put(q, *d);
    return 0;
}

static void* consume(void *a) {
    Params *p;
    p = (Params *) a;
    Deq q = (Deq) p->q;
    mole_whack(mtq_head_get(q));
    printf("Consumerism\n");
    return 0;
}

int main() {
    srandom(time(0));
    // initialize vars
    int n = 30;
    Deq q = deq_new();
    Lawn lawn = lawn_new(0, 0);
    // initialize params
    Params *params;
    params = (Params *) malloc(sizeof(Params));
    params->q = q;
    params->lawn = lawn;
    // create threads
    pthread_t threads[n * 2];
    for (int i = 0; i < n * 2;) {
        pthread_create(&threads[i++], 0, produce, (void *) params);
        pthread_create(&threads[i++], 0, consume, (void *) params);
    }
    // join threads
    for (int i = 0; i < n * 2;) {
        pthread_join(threads[i++], 0);
        pthread_join(threads[i++], 0);
    }
    // free vars
    free(params);
    free_mtq();
    lawn_free(lawn);
    deq_del(q, 0);
}
