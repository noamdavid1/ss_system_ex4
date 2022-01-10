#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "algo.h"
#include "pq.h"
#include "edges.h"

#define infinitiy __INT_MAX__

graph *gra;

int size;
int good;

void build_graph_cmd(graph *head)
{
    gra= head;
    gra->gsize=head->gsize;
    gra->init= 1;
}

void insert_node_cmd(pnode head)
{
    pnode n=gra->head;
    if (n->node_num==head->node_num)
    {
        pnode tmp=n->next;
        free_the_edges(n);
        n=head;
        gra->head=head;
        n->next=tmp;
        n->edges=head->edges;
        update_edges(head);
        return;
    }
    while (n->next!=NULL) 
    {
        if (n->next->node_num==head->node_num)
        {
            pnode tmp=n->next->next;
            free_the_edges(n->next);
            n->next=head;
            n->next->next=tmp;
            n->next->edges=head->edges;
            update_edges(head);
            return;
        }
        n=n->next;
    }
    pnode tmp=gra->head;
    gra->head=(pnode)head;
    gra->head->next=tmp;
    gra->gsize++;
}

void delete_node_cmd(int id)
{
    node *dnode=gra->head;
    if (dnode->node_num==id)
    {
        gra->head=dnode->next;
        free_the_edges(dnode->next);
        free(dnode);
        free_edges(id);
        return;
    }
    while (dnode->next!=NULL)
    {
        if (dnode->next->node_num==id)
        {
            pnode tmp=dnode->next->next;
            free_edges(id);
            free_the_edges(dnode->next);
            dnode->next = tmp;
            return;
        }
        dnode=dnode->next;
    }
}

void printGraph_cmd(graph *gra)
{
    pnode n=gra->head;
    while (n!=NULL)
    {
        printf("Node %d:\n", n->node_num);
        pedge edge = n->edges;
        while (edge!=NULL)
        {
            printf("src: %d, dest: %d, w = %d ", n->node_num, edge->endpoint->node_num, edge->weight);
            edge=edge->next;
        }
        n=n->next;
    }
    if (n==NULL)
    {
        printf("empty graph");
    }
    printf("\n");
}

void deleteGraph_cmd(pnode *head)
{
    pnode n= *head;
    pnode del_node;
    pedge del_edge;

    while (n!=NULL)
    {
        pedge edge=n->edges;
        while(edge!=NULL)
        {
            del_edge=edge;
            edge=edge->next;
            free(del_edge);
        }
        del_node=n;
        n=n->next;
        free(del_node);
    }
}

void shortsPath_cmd(int src, int dest)
{
    pnode n=gra->head;
    pnode source;
    while (n!=NULL)
    {
        n->dist=infinitiy;
        n->tag=NULL;
        n->visited=0;
        if (n->node_num==src)
            source = n;
        n=n->next;
    }
    source->dist=0;
    ptrpq pq=new_priorityqueue(source);
    pq->head->pqnext=NULL;


    pedge edge=(pedge)malloc(sizeof(edge));
    int weight;
    pnode short_path=NULL;
    free(edge);
    while (!isEmpty())
    {
        n= pop();
        n->visited=1;
        if (n->node_num==dest){
            short_path = n;
        }    
        weight=n->dist;
        edge=n->edges;

        while (edge!=NULL)
        {
            if (weight+edge->weight<edge->endpoint->dist)
            {
                edge->endpoint->tag=n;
                edge->endpoint->dist=weight+edge->weight;
            }
            if (edge->endpoint->visited==0)
                push(edge->endpoint,pq);
            edge=edge->next;
        }
    }
    free(pq);
    free(edge);
    if (short_path==NULL)
    {
        printf("-1\n");
        return;
    }
    printf("Dijsktra shortest path: %d \n", short_path->dist);

}

bool findNode(int id, int arr[], size_t length)
{
    int nodefound= id;
    for (int i = 0; i < sizeof(int) * length; i++)
    {
        if (arr[i]==nodefound)
            return true;
    }
    return false;
}

void per(int mat[size][size], size_t len, int count, int i, int arr[], bool visit[size], int lev, int sumof)
{
    if (lev==count)
    {
        if (sumof<good)
            good=sumof;
        return;
    }
    visit[i]= true;
    for (int j = 0; j < size; j++)
    {
        if (visit[j]!=true&&mat[i][j]!=-1)
        {
            if (!findNode(j,arr,len)){
                per(mat,len,count,j,arr,visit,lev,sumof+mat[i][j]);
            }    
            else{
                per(mat,len,count,j,arr,visit,lev+1,sumof+mat[i][j]);
            }    
            visit[j]=false;
        }
    }
    visit[i]=false;
    return;
}

void TSP_cmd(int path[], int k)
{
    int maximum=0;
    pnode n=gra->head;
    while(n!=NULL)
    {
        if(n->node_num>maximum){
            maximum=n->node_num;
        }    
        n=n->next;
    }
    size=maximum+1;
    int mat[size][size];
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            mat[i][j]=-1;
        }
    }
    n=gra->head;
    pedge edge;
    while (n!=NULL)
    {
        edge = n->edges;
        while (edge!=NULL)
        {
            mat[n->node_num][edge->dest] = edge->weight;
            edge = edge->next;
        }
        n=n->next;
    }

    bool visited[size];
    memset(visited, false, sizeof(bool) * size);
    int tsp=infinitiy;

    n=gra->head;
    size_t len=k;
    if (k>2)
    {
        k++;
    }
    int x= 1;
    while (n!=NULL)
    {
        memset(visited,false,sizeof(bool)*size);
        good= infinitiy;
        x= n->node_num;
        if (findNode(x,path,len)){
            per(mat,len,k,x,path,visited,1,0);
        }    
        else{
            per(mat,len,k,x,path,visited,0,0);
        }    
        if (good<tsp){
            tsp=good;
        }    
        n=n->next;
    }

    if (tsp==infinitiy){
        tsp= -1;
    }    
    printf("TSP shortest path: %d\n", tsp);
}