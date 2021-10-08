#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include "mtq.h"

typedef struct Params {
    Mtq q;
    Lawn lawn;
} *Params;

static void *produce(void *a) {
    void **args = a;
    Mtq q = (Mtq)args[0];
    Lawn l = (Lawn)args[1];
    deq_tail_put((Deq) q, mole_new(l, 0, 0));
    return 0;
}

static void consume(void *params) {
//    mole_whack(deq_head_rem((Mtq) ((Params*)params)->q, deq_head_get((Mtq) ((Params*)params)->q)));
}

int main() {
    Mtq q = deq_new();
    srandom(time(0));
    const int n = 10;
    Lawn lawn = lawn_new(0, 0);
//    for (int i = 1; i <= n; i++)
//        consume(produce(lawn, q), q);
    Params params = (Params) malloc(sizeof(Params));
    params->q = q;
    params->lawn = lawn;
    create_n_threads(10, produce, params);
    lawn_free(lawn);
}
