//
// Created by pb400 on 10/7/2021.
//

#ifndef CS452_HW2_MTQ_H
#define CS452_HW2_MTQ_H

#include "mole.h"
#include "deq.h"

extern void mtq_tail_put(Deq q, Mole m);

extern Data mtq_head_get(Deq q);

extern void free_mtq();

#endif //CS452_HW2_MTQ_H
