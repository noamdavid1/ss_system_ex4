#ifndef PRIO_Q
#define PRIO_Q
#include "algo.h"

typedef struct priority_queue
{
    int size;
    pnode head;
} pq, *ptrpq;

int isEmpty();
pnode peek();
pnode pop(); 
ptrpq new_priorityqueue(pnode head);
void push(pnode node, ptrpq pr);

#endif