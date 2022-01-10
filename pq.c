#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "pq.h"
#include "algo.h"

ptrpq pr_q = NULL;

int isEmpty()
{
    if (pr_q->size != 0)
    {
        return false;
    }
    return true;
}

pnode peek(){
    return pr_q->head;
}

pnode pop(){
    pnode ans = pr_q->head;
    pr_q->head = ans->pqnext;
    pr_q->size--;
    ans->pqnext = NULL;
    return ans;
}


ptrpq new_priorityqueue(pnode head)
{
    ptrpq pq = (ptrpq)malloc(sizeof(pq)+sizeof(node));
    pq->size = 1;
    pq->head = head;
    pq->head->pqnext = NULL;
    pr_q = pq;
    pr_q->head = head;
    return pq;
}

void push(pnode node, ptrpq pr){
    if (isEmpty())
    {
        pr_q->head = node;
        pr_q->size = 1;
        return;
    }

    if (node->dist < pr_q->head->dist)
    {
        node->pqnext =  pr_q->head;
        pr_q->head = node;
        pr_q->size++;
        return;
    }
    pr->head->pqnext = NULL;
    while (pr->head->pqnext != NULL)
    {
        if (node->dist < pr->head->pqnext->dist)
        {
            node->pqnext = pr->head->pqnext;
            pr->head->pqnext = node;
            pr_q->size++;
            return;
        }
        pr->head = pr->head->pqnext;
        pr_q++;
    }
    pr->head->pqnext = node;
}
