#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "algo.h"
#include "edges.h"


void getcharfunc(char *c)
{
    scanf("%c", c);
    if(*c==' '){
        scanf("%c",c);
    }    
}

pnode getNode(int id, graph *gra)
{
    pnode n=gra->head;
    while (n!=NULL)
    {
        if (n->node_num==id)
        {
            return n;
        }
        n=n->next;
    }
    return false;
}

int main()
{
    bool boolean=true;
    char input=' ';
    int num= 1;
    int k= 1;
    int *array;
    array=(int*)calloc(6, sizeof(int));
    pnode n=(pnode)malloc(sizeof(node));
    n->next=NULL;
    pnode n2=(pnode)malloc(sizeof(node));
    pedge e=(pedge)malloc(sizeof(edge));
    graph *gra=(graph *)malloc(sizeof(graph));
    gra->head=NULL;
    gra->head=n;
    gra->init=0;
    gra->gsize=0;
    input=getchar();

    while (input!=EOF||input!='\n')
    {
     SC:
        if(input== 'A')
        {
            getcharfunc(&input);
            gra->gsize=(input-'0');
            pnode arr[gra->gsize];
            for (int i = 0; i < gra->gsize; i++)
            {
                arr[i]=(pnode)malloc(sizeof(node));
            }
            while (true)
            {
                getcharfunc(&input);
                if (input=='A'||input=='B'||input=='D'||input=='S'||input=='T'||input=='E'||input==EOF||input=='\n')
                {
                    gra->head=n->next;
                    func_endpoint(gra,arr);
                    build_graph_cmd(gra);
                    free(n);
                    for (int i = 0; i < gra->gsize; i++)
                    {
                        free(arr[i]);
                    }
                    goto SC;
                    break;
                }

                if (input=='n'||input=='N')
                {
                    n2->next=n->next;
                    n->next=(pnode)malloc(sizeof(node));
                    n->next->next = n2->next;
                    n->next->edges=NULL;
                    n->next->tag=NULL;
                    boolean=true;
                }
                else
                {
                    if (boolean)
                    {
                        n->next->node_num=(input-'0');
                        arr[input-'0']->next=n->next;
                        boolean=false;
                    }
                    else
                    {
                        e->next=n->next->edges;
                        n->next->edges=(pedge)malloc(sizeof(struct edge_));
                        n->next->edges->dest=(input-'0');
                        n->next->edges->endpoint=NULL;
                        scanf(" %c",&input);
                        n->next->edges->weight=(input-'0');
                        n->next->edges->next=e->next;
                    }
                }
            }
            func_endpoint(gra,arr);
            free(n->edges);
            free(n->next->edges);
            free(n->next);
            free(n->pqnext);
            free(n->tag);
            break;
        }
        else if(input== 'B')
        {
            getcharfunc(&input);
            n=(pnode)malloc(sizeof(node) + sizeof(node));
            n->node_num=(input-'0');
            n->next=NULL;
            n->edges=NULL;

            while(true)
            {
                getcharfunc(&input);
                if (input=='A'||input=='B'||input=='D'||input=='S'||input=='T'||input==EOF||input=='\n')
                {
                    insert_node_cmd(n);
                    goto SC;
                    break;
                }

                e->next=n->edges;
                n->edges=(pedge)malloc(sizeof(edge));
                n->edges->dest=(input-'0');
                n->edges->endpoint = getNode(n->edges->dest, gra);
                getcharfunc(&input);
                n->edges->weight=(input-'0');
                n->edges->next=e->next;
            }
            insert_node_cmd(n);
            free(n->edges);
            free(n->next->edges);
            free(n->next);
            free(n->pqnext);
            free(n->tag);
            break;
        }
        else if(input=='D')
        {
            getcharfunc(&input);
            delete_node_cmd(input-'0');
            break;
        }
        else if(input=='S')
        {
            getcharfunc(&input);
            num=(input-'0');
            getcharfunc(&input);
            shortsPath_cmd(num,(input-'0'));
            getcharfunc(&input);
            goto SC;
            break;
        }
        else if (input== 'T')
        {
            getcharfunc(&input);
            k = (input - '0');
            array = realloc(array,k+1);
            free(array);
            array = calloc(k + 10, sizeof(int) + 1);
            int i = 0;
            while (true)
            {
                getcharfunc(&input);
                if (input == 'A' || input == 'B' || input == 'D' || input == 'S' || input == 'T' || input == EOF || input == '\n')
                {
                    TSP_cmd(array, k);
                    goto SC;
                    break;
                }

                array[i++]=input-'0';
            }
            TSP_cmd(array,k);
            goto SC;
            break;
        }
        }
    free(e);
    free(array);
    free(n2);
    deleteGraph_cmd(&(gra->head));
    free(gra);
    return 0;
    }