#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include "mtq.h"

/**
 * Params struct to pass parameters to children threads
 */
typedef struct Params {
    Deq q;
    Lawn lawn;
} Params;

/**
 * Produce a new Mole and add it to the beginning of the mtq
 * @param a - Parameters containing the proper Lawn and Deq
 * @return - 0
 */
static void *produce(void *a) {
    // cast a to a Params pointer
    Params *p;
    p = (Params *) a;
    // get parameters
    Deq q = p->q;
    Lawn l = p->lawn;
    // put new Mole in Mtq
    mtq_tail_put(q, mole_new(l, 0, 0));
    return 0;
}

/**
 * Consume the Mole at the end of the Mtq
 * @param a - Parameters containing the proper Deq
 * @return - 0
 */
static void *consume(void *a) {
    // cast a to a Params pointer
    Params *p;
    p = (Params *) a;
    // get Deq
    Deq q = p->q;
    // whack the mole >:)
    mole_whack(mtq_head_get(q));
    return 0;
}

/**
 * Creates n threads of produce and consume.
 * @param threads - Array containing all threads
 * @param params - Struct of parameters to pass to functions
 * @param n - Number of threads to create of each function
 */
static void create_threads(pthread_t *threads, void *params, int n) {
    for (int i = 0; i < n * 2;) {
        pthread_create(&threads[i++], 0, produce, (void *) params);
        pthread_create(&threads[i++], 0, consume, (void *) params);
    }
}

/**
 * Joins n threads
 * @param threads - Array of threads to join
 * @param n - Number of each type of thread to join
 */
static void join_threads(pthread_t *threads, int n) {
    for (int i = 0; i < n * 2;) {
        pthread_join(threads[i++], 0);
        pthread_join(threads[i++], 0);
    }
}

int main() {
    srandom(time(0));
    // number of threads to run of each consume and produce
    int n = 100;
    // initialize vars
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
    join_threads(threads, n);
    // free vars
    free(params);
    free_mtq();
    lawn_free(lawn);
    deq_del(q, 0);
}
