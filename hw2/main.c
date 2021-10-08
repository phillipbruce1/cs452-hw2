#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include "mtq.h"

typedef struct Params {
    Lawn lawn;
    Deq deq;
} Params;

static void *produce(void *params) {
    deq_tail_put((Deq) params->deq, mole_new((Lawn) params->lawn, 0, 0));
    return deq_tail_get((Deq) params->q);
}

static void consume(void *params) {
    mole_whack(deq_head_rem((Deq) params->deq, deq_head_get((deq) params->deq)));
}

int main() {
    Deq q = deq_new();
    srandom(time(0));
    const int n = 10;
    Lawn lawn = lawn_new(0, 0);
//    for (int i = 1; i <= n; i++)
//        consume(produce(lawn, q), q);
    Params *params = (Params) malloc(sizeof(Params));
    params->deq = q;
    params->lawn = lawn;
    create_n_threads(10, produce, *params);
    lawn_free(lawn);
}
