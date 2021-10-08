#include <pthread.h>

#include "mtq.h"
#include "lawn.h"
#include "deq.h"

static void create_n_threads(int n, void *function, void *params) {
    for (int i = 0; i < n; i++)
        pthread_create(i, 0, function, (Lawn) params->lawn, (Deq) params->deq);
}