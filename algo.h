#ifndef ALGO_
#define ALGO_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_
{
    int weight;
    int dest;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_
{
    int dist;
    struct GRAPH_NODE_ *tag;
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int visited;
    struct GRAPH_NODE_ *pqnext; 
} node, *pnode;

typedef struct graph_{
    int init;
    int gsize;
    pnode head;
} graph, *pgraph;


void build_graph_cmd(graph *g);
void insert_node_cmd(pnode head);
void delete_node_cmd(int id);
void printGraph_cmd(graph *g); 
void deleteGraph_cmd(pnode *head);
void shortsPath_cmd(int src, int dest);
void TSP_cmd(int *cities, int k);

#endif