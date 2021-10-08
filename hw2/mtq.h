//
// Created by pb400 on 10/7/2021.
//

#ifndef CS452_HW2_MTQ_H
#define CS452_HW2_MTQ_H

#include "mole.h"
#include "deq.h"

typedef void* Mtq;

extern void create_n_threads(int n, void *function, void *params);

extern void mtq_tail_put(Deq q, Mole m);

extern void mtq_head_get(Deq q);

#endif //CS452_HW2_MTQ_H
