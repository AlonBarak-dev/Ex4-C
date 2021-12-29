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

void dijkstra_path(pnode head, int src, int dest, int *arr){


    pnode counter = head;
    int n = 0;
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
    int parents[n];
    for(int i = 0; i < n; i++){
        visited[i] = 0;
        parents[i] = -1;
    }
    
   parents[src] = -1;
    
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
    
        w = findMin(distance, visited, n);
        visited[w] = 1;

        for (int v = 0; v < n; v++)
        {
            if(visited[v] == 0){
                distance[v] = min(distance[v], distance[w] + adjList[w][v]);
                if (distance[v] == distance[w] + adjList[w][v])
                {
                    parents[v] = w;
                }
                
            }
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        arr[i] = -1;
    }

    int ctr = 0;
    if (visited[dest] == 1)
    {   
        int j = dest;
        while(1){

            if(parents[j] == -1){
                arr[ctr] = j;
                break;
            }
            else{
                arr[ctr] = parents[j];
                j = parents[j];
            }

        }
    }
    
}

int min_shortsPath(pnode head, int v, int visited[], int cities[], int n){

    int min_dist = INT_MAX;
    int u = -1;

    for (int i = 0; i < n; i++)
    {
        int visit = 0;
        int dist;
        for (int j = 0; j < n; j++)
        {
            if (visited[j] == cities[i])
            {
                visit = 1;      // if we visited the node, dont include him
            }
        }
        if(!visit){     // do only if we not visited the node
            dist = dijkstra(head,v,cities[i]);
            if (dist < min_dist)
            {
                min_dist = dist;
                u = cities[i];
            }
            
        }
    }
    if ((min_dist == INT_MAX)||(min_dist == -2147483644))
    {
        u = -1;
    }
    
    return u;

}


int allVisited(int visited[], int n){      
    /*
        this method return 1 if we visited in all the nodes, 0 else
    */
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            return 0;
        }
    }
    return 1;
    
}

void TSP_cmd(pnode head, char *ch){

    pnode counter = head;
    int size = 0;
    // find the current size of the graph
    while (counter != NULL)
    {
        size++;
        counter = counter->next;
    }


    int n = 6;
    int input[n];      // array of input

    // initialize the input needs to visit in, input[0] is the first destination
    int i = 0;
    scanf(" %c", ch);
    while((*ch >= '0') && (*ch <= '9')){
        input[i] = *ch - '0';
        scanf(" %c", ch);
        i++;
    }
    for(int j = i; j < n; j++){
        input[j] = -1;
    }
    int p = 0;
    while(input[p] != -1){     //find the exact number of input
        p++;
    }

    int cities[p];
    for (int j = 0; j < p; j++)
    {
        cities[j] = input[j];
    }
    // now cities contain only the nodes IDs

    int min_dist = INT_MAX;
    int path[size];
    for (int i = 0; i < p; i++)
    {
        int curr_dist = 0;
        int visited[p];     // help us to see nodes we already visited in
        for (int j = 0; j < p; j++)
        {
            visited[j] = 0;
        }
        
        int v = cities[i];
        int ctr = 0;
        visited[ctr] = v;      //mark start node as visited
        ctr++;
        while (allVisited(visited, p) != 1)        // loop until we visit all the nodes
        {
            int u = min_shortsPath(head, v, visited, cities,p);        // return the closest node to v
            if(u == -1){
                curr_dist = INT_MAX;
                break;
            }
            int dist = dijkstra(head,v,u);      // return the distance from v to u
            dijkstra_path(head,v,u, path);        // return the path from v to u

            curr_dist += dist;
            for(int j = 0; (j < size) && (path[j] != -1); j++)
            {
                for (int i = 0; i < p; i++)
                {
                    if (path[j] == cities[i])
                    {
                        visited[ctr] = *path;       // if we visited in one of the cities during a travel, mark it
                        ctr++;
                    }
                }
                
            }

            v = u;      // move to the next node  
        }

        min_dist = min(min_dist, curr_dist);
    }
    
    printf("TSP shortest path: %d\n", min_dist);

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


   
