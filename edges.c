#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "algo.h"
#include "pq.h"

graph *gra;

void update_edges(pnode new_node)
{
    pnode n=gra->head;
    pedge edge;
    while (n!=NULL)
    {
        edge=n->edges;

        while (edge!=NULL)
        {
            if (edge->dest==new_node->node_num)
            {
                edge->endpoint=new_node;
            }
            edge=edge->next;
        }
        n=n->next;
    }
}

void func_endpoint(graph *gra, pnode *arr)
{
    pnode n=gra->head;
    pedge edge=NULL;

    while(n!=NULL)
    {
        edge=n->edges;
        while(edge!=NULL)
        {
            edge->endpoint=arr[edge->dest]->next;
            edge=edge->next;
        }
        n=n->next;
    }
}

void free_edges(int id)
{
    pnode n=NULL;
    n=gra->head;
    pedge edge1=NULL;
    pedge edge2=NULL;
    while (n!=NULL)
    {
        edge1=n->edges;
        if(edge1==NULL)
        {
            n=n->next;
            continue;
        }

        if(n->edges->dest==id)
        {
            edge1->endpoint=NULL;
            n->edges=edge1->next;
            n=n->next;
            free(edge1);
            free(edge2);
            continue;
        }

        while(edge1!=NULL)
        {
            if(edge1->dest==id)
            {
                edge1->endpoint=NULL;
                edge2->next=edge1->next;
            }
            edge2=edge1;
            edge1=edge1->next;
        }
        n=n->next;
    }
    free(edge1);
    free(edge2);
    free(n);
}

void free_the_edges(pnode head)
{
    edge *next=head->edges;
    pedge removedge=NULL;
    while(next!=NULL)
    {
        removedge=next;
        next=next->next;
        free(removedge);
    }
    free(next);
    free(head);
}