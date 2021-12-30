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

} node, *pnode;

void build_graph_cmd(pnode *head, int size, char **ch);
void insert_node_cmd(pnode *head, char **ch);
void add_edges_to_node(pnode *head, pnode *node, int id, char **ch);
void delete_node_cmd(pnode *head, char **ch);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head, char **ch);
void TSP_cmd(pnode head, char **ch);
int toNum(char **data);
void TSP_cmd2(pnode head, char **ch);

#endif
