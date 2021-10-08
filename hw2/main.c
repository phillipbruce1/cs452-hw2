#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"

static Mole produce(Lawn l, Deq q) {
    deq_tail_put(q, mole_new(l, 0, 0));
    return deq_tail_get(q);
}

static void consume(Mole m, Deq q) {
    mole_whack(deq_head_rem(q, m));
}

int main() {
    Deq q = deq_new();
    srandom(time(0));
    const int n = 10;
    Lawn lawn = lawn_new(0, 0);
    for (int i = 1; i <= n; i++) {
        produce(lawn, q);
        consume(deq_head_get(q), q);
    }
    lawn_free(lawn);
}
