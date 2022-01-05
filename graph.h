#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    //int seq;
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
int toNum(char **data);
pnode newnode(int k, pnode next);
pnode find_node(int data, pnode head);
pnode generate(int k);
void remove_out_edges(pnode here);
void remove_edge_to(int data, pnode here);
pnode insert_node(int data, pnode *head);
pedge new_edge(int weight, pedge next, pnode dest);


#endif
