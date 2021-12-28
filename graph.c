#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"



void build_graph_cmd(pnode *head, int size, char *ch){

    // in case the malloc failed, exit
    if(! *head){
        printf("Couldn't allocate memory for head Node");
        exit(0);
    }

    

    node **cpy = head;
    for(int i = 0; i < size-1; i++){
        (*cpy)->next = (pnode)malloc(sizeof(node));
        cpy = &((*cpy)->next);
    }

    node *ptr = *head;
    node *next;

    for (int i = 0; i < size; i++)
    {
        if (i > 2)
            {
                next = NULL;
            }
        else{ 
                next = (*ptr).next;
            }
    
        
        (*ptr).node_num = i;
        (*ptr).next = next;
        (*ptr).edges = NULL;
        
        ptr = ptr->next;
        
    }

    node *ptr2;
    scanf(" %c", ch);
    while (*ch == 'n')
    {
        ptr2 = *head;
        scanf(" %c", ch);
        int node_id = *ch - '0';
        while ((*ptr2).node_num != node_id)
        {
            ptr2 = (*ptr2).next;
        }
        
        add_edges_to_node(head, &ptr2, node_id, ch);
    }
    
}


void add_edges_to_node(pnode *head, pnode *node, int id, char *ch){

    scanf(" %c", ch);
    edge *edges;
    if((*ch <= '9') && (*ch >= '0')){
        edges = (pedge)malloc(sizeof(edge));
        (*node)->edges = edges;
    }
    else{
        (*node)->edges = NULL;  //dont have edges
        return;
    }
    while (!(*ch < '0') && !(*ch > '9'))
    { 
        
        int dest = *ch - '0';
        pnode dst = *head;
        while ((*dst).node_num != dest)
        {
            dst = (*dst).next;
        }
        
        scanf(" %c", ch);
        int weight = *ch - '0';
        
        (*edges).endpoint = dst;
        (*edges).weight = weight;
        if(scanf(" %c", ch) == EOF){
            break;
        }
        if((*ch <= '9') && (*ch >= '0')){
            (*edges).next = (pedge)malloc(sizeof(edge));
            edges = (*edges).next;
        }
        else{
            (*edges).next = NULL;
        }
    }
}


void deleteGraph_cmd(pnode *head){

    if (! *head)
    {
        return;
    }
    

    pnode * nodes = head;
    pedge * edges = NULL;
    pnode pn = NULL;
    pedge pe = NULL;

    while ((*nodes) != NULL)
    {
        edges = &((*nodes)->edges);
        while ((*edges) != NULL)
        {
            pe = (*edges);
            edges = &((*edges)->next);
            free(pe);
        }

        pn = (*nodes);
        nodes = &((*nodes)->next);
        free(pn);
        
    }

}


void insert_node_cmd(pnode *head, char *ch){

    pnode ptr2 = *head;
    pedge *edges = NULL;
    scanf(" %c", ch);
    pedge pe = NULL;
    int node_id = *ch - '0';
    while ((*ptr2).node_num != node_id && (*ptr2).next != NULL)
    {
        ptr2 = (*ptr2).next;
    }
    if ((*ptr2).next == NULL && (*ptr2).node_num != node_id)
    {
        (*ptr2).next = (pnode)malloc(sizeof(node));
        ptr2 = (*ptr2).next;
        (*ptr2).node_num = node_id;
    }
    else {
        edges = &((*ptr2).edges);
        while ((*edges) != NULL)
        {
            pe = *edges;
            edges = &((*edges)->next);
            free(pe);
        }
    }
    add_edges_to_node(head, &ptr2, node_id, ch);

}


void delete_node_cmd(pnode *head, char *ch){

    scanf(" %c", ch);

    int node_id = *ch - '0';        // the id of the node we want to delete

    pnode *ptr = head, node = NULL;
    pedge *edges = NULL, pne = NULL;
    while (*ptr != NULL)     // delete edges to node_id
    {
        if((*ptr)->node_num == node_id){     // the desired node 
            edges = &((*ptr)->edges);
            while(*edges != NULL){
                pne = *edges;
                *edges = (*edges)->next;
                free(pne);
            }
            node = *ptr;
            ptr = &((*ptr)->next);
            continue;
        }

        edges = &((*ptr)->edges);
        if(*edges != NULL){
            while ((*edges)->next != NULL)
            {
                if ((*(*(*edges)->next).endpoint).node_num == node_id)
                {
                    pne = (*edges)->next;
                    (*edges)->next = (*(*edges)->next).next;
                    free(pne);
                    break;
                }
                else
                {
                    edges = &((*edges)->next);
                }

            }
            edges = &((*ptr)->edges);
            if((*(*edges)->endpoint).node_num == node_id){
                pne = *edges;
                *edges = (*edges)->next;
                free(pne);
            }
        }
        ptr = &((*ptr)->next);
    }
    pnode *ptr2 = head;
    while ((*ptr2)->next->node_num != node_id)
    {
        ptr2 = &((*ptr2)->next);
    }
    (*ptr2)->next = ((*ptr2)->next)->next;
    
    free(node);
}

int min(int a, int b){
    if(a < b){
        return a;
    }
    else{
        return b;
    }
}

int findMin(int distance[], int visited[], int n){

    int min = INT_MAX;
    int w = 0;
    for (int i = 0; i < n; i++)
    {
        if ((visited[i] == 0) && (distance[i] < min))
        {
            min = distance[i];
            w = i;
        }
        
    }
    return w;
}


int dijkstra(pnode head, int src, int dest){


    pnode counter = head;
    int n = 0;
    int shortestPath = 0;
    // find the current size of the graph
    while (counter != NULL)
    {
        n++;
        counter = counter->next;
    }

    int adjList[n][n];
    // initialize adj array with infinety values at the begining
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjList[i][j] = INT_MAX;
        }
    }

    pnode nodes = head;
    pedge edges = NULL;
    // insert the weights of the edges into the adj matrix
    while (nodes != NULL)
    {
        edges = (*nodes).edges;
        while (edges != NULL)
        {
            adjList[nodes->node_num][edges->endpoint->node_num] = edges->weight;
            edges = (*edges).next;
        }
        nodes = (*nodes).next;
    }
    
    // initilaize the visited array to zeros at the begining
    int visited[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
    }

    visited[src] = 1;       // mark the source node as visited

    // initilaize the distances from source to all nodes
    int distance[n];
    for (int i = 0; i < n; i++)
    {
        if (i == src)
        {
            distance[i] = 0;
        }
        else{
            distance[i] = adjList[src][i];
        }
    }

    int w;
    for (int i = 0; i < n; i++)
    {
        if (i != src)
        {
            w = findMin(distance, visited, n);
            visited[w] = 1;

            for (int v = 0; v < n; v++)
            {
                if(visited[v] == 0){
                    distance[v] = min(distance[v], distance[w] + adjList[w][v]);
                }
            }
            
            
        }
        
    }
    
    shortestPath = distance[dest];
    return shortestPath;
}




void shortsPath_cmd(pnode head, char *ch){

    scanf(" %c", ch);
    int src = *ch - '0';

    scanf(" %c", ch);
    int dest = *ch - '0';

    int path = dijkstra(head, src, dest);

    printf("Dijsktra shortest path: %d\n", path);


}


void printGraph_cmd(pnode head){

    
    pnode ptr = head;
    pedge edges;
    while(ptr != NULL){
        edges = (*ptr).edges;
        printf("node number: %d\n", ptr->node_num);
        while (edges != NULL)
        {
            printf("dest: %d\n", edges->endpoint->node_num);
            printf("weight : %d\n", edges->weight);
            edges = edges->next;
        }
        ptr = ptr->next;
        
    }

}


   
