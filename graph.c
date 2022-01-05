#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"


int toNum(char **data){

    char *ptr = *data;      // a pointer to the data pointer
    char arr[6];        // the array which save the chars
    int i = 0;
    while ((*ptr != ' ') && (*ptr != '\n'))     // loop until a space or EOF is located
    {
        arr[i] = *ptr;
        ptr++;
        i++;
    }
    if (i < 6)
    {
        arr[i] = '\0';      // tells atoi to stop
    }
    
    
    int number = atoi(arr);     // convert the char array to a number
    ptr++;
    *data = ptr;

    return number;
}

void printGraph_cmd(pnode head){
    /*
    printing the graph for self debug reasons
    */
    pnode ptr = NULL;
    ptr = head;
    pedge edges = NULL;
    while (ptr != NULL)
    {
        edges = (*ptr).edges;
        printf("node number: %d\n", ptr->node_num);
        while (edges != NULL)
        {
            printf("dest: %d    ,   ", edges->endpoint->node_num);
            printf("weight: %d\n", edges->weight);
            edges = edges->next;
        }
        ptr = ptr->next;
    }
}

void build_graph_cmd(pnode *head, int size, char **ch){


    char *chptr = *ch;
    // in case the malloc returned NULL
    if (!head)
    {
        printf("Couldn't allocate memory for the head of the graph");
        exit(0);
    }

    if(size == 0){      // in case the graph is size 0, return and do nothing
        return;
    }
    
    // allocate memory for all nodes and connect them to each other
    node **cpy = NULL;
    cpy = head;
    for (int i = 0; i < size-1; i++)
    {
        (*cpy)->next = (pnode)malloc(sizeof(node));
        cpy = &((*cpy)->next);
    }

    node *ptr = *head;
    node *next = NULL;

    for (int i = 0; i < size; i++)
    {
        if (i > size-2)
        {
            next = NULL;        // last node in the graph points to NULL
        }
        else{
            next = (*ptr).next;
        }
        
        // define the node values
        (*ptr).node_num = i;
        (*ptr).next = next;
        (*ptr).edges = NULL;

        ptr = ptr->next;    // move to the next node
    }

    node *ptr2 = NULL;
    while (*chptr == 'n')
    {
        ptr2 = *head;
        chptr += 2;
        int node_id = toNum(&chptr);        // the node we will add edges to
        while ((ptr2->node_num != node_id))
        {
            ptr2 = (*ptr2).next;
        }

        add_edges_to_node(head, &ptr2, node_id, &chptr);    // add edges to the node
        
    }
    
    *ch = chptr;    // forward the data pointer to the new position
}


void add_edges_to_node(pnode *head, pnode *node, int id, char **ch){

    char *chptr = *ch;
    edge *edges = NULL;

    if ((*chptr <= '9') && (*chptr >= '0'))
    {
        edges = (pedge)malloc(sizeof(edge));    // the node have edges
        (*node)->edges = edges;
    }
    else{
        (*node)->edges = NULL;  // the node dont have edges
        return;
    }

    while ((*chptr >= '0') && (*chptr <= '9'))
    {
        int dest = toNum(&chptr);   // the dest node
        pnode dst = NULL;
        dst = *head;
        while ((*dst).node_num != dest)
        {
            dst = (*dst).next;      // the endpoint node of the edge
        }

        int weight = toNum(&chptr);     // the weight of the edge

        (*edges).endpoint = dst;
        (*edges).weight = weight;
        if (*chptr == '\0')
        {
            break;
        }
        if ((*chptr <= '9') && (*chptr >= '0'))     // there is another edge
        {
            (*edges).next = (pedge)malloc(sizeof(edge));
            edges = (*edges).next;
        }
        else{
            (edges)->next = NULL;
        }
    }
    *ch = chptr;        // forward the data pointer to the new position
}


void deleteGraph_cmd(pnode *head){



    // initialize pointers
    pnode *nodes = NULL;
    nodes = head;
    pedge *edges = NULL;
    pnode pn = NULL;
    pedge pe = NULL;

     if(!nodes){      // base case
        return;
    }

    while ((*nodes) != NULL)
    {
        edges = &((*nodes)->edges);  // the edges of the node
        while ((*edges) != NULL)
        {
            pe = *edges;
            edges = &((*edges)->next);
            free(pe);       // delete and free the edge
        }

        pn = *nodes;
        nodes = &((*nodes)->next);
        free(pn);   // delete and free the node
         
    }
}


void insert_node_cmd(pnode *head, char **ch){

    char *chptr = *ch;
    // initilaize pointers
    pnode ptr2 = NULL;
    ptr2 = *head;
    pedge *edges = NULL;
    pedge pe = NULL;

    int node_id = toNum(&chptr);        // the id of the new node

    while (((*ptr2).node_num != node_id) && ((*ptr2).next != NULL))     // search for the node in the graph
    {
        ptr2 = (*ptr2).next;
    }
    if (((*ptr2).next ==  NULL) && ((*ptr2).node_num != node_id))       // if the node is a new node
    {
        (*ptr2).next = (pnode)malloc(sizeof(node));
        ptr2 = (*ptr2).next;
        (*ptr2).node_num = node_id;
    }
    else{           // if the node is a node in the graph
        edges = &((*ptr2).edges);
        while ((*edges) != NULL)
        {
            pe = *edges;
            edges = &((*edges)->next);
            free(pe);
        }
    }
    
    add_edges_to_node(head, &ptr2, node_id, &chptr);        // add edges to the node
    *ch = chptr;        // forward the data pointer 
}


void delete_node_cmd(pnode *head, char **ch){

    char *chptr = *ch;
    int node_id = toNum(&chptr);        // the node we want to delete

    pnode *ptr = NULL, node = NULL;
    pedge *edges = NULL, pne = NULL;
    ptr = head;
    while (*ptr != NULL)
    {
        if ((*ptr)->node_num == node_id)        // delete the edges of the node
        {
            edges = &((*ptr)->edges);
            while (*edges != NULL)
            {
                pne = *edges;
                *edges = (*edges)->next;
                free(pne);
            }
            node = *ptr;
            ptr = &((*ptr)->next);
            continue;
        }

        // do if the current node is not the desired node
        edges = &((*ptr)->edges);
        
        // delete edges from any node to node_id 
        if (*edges != NULL)
        {
            while ((*edges)->next != NULL)
            {
                if ((*(*(*edges)->next).endpoint).node_num == node_id)
                {
                    pne = (*edges)->next;
                    (*edges)->next = (*(*edges)->next).next;
                    free(pne);
                    break;
                }
                else{
                    edges = &((*edges)->next);
                }
                
            }
            // in case there is only one edge to some node, if its to node_id then delete
            edges = &((*ptr)->edges);
            if ((*(*edges)->endpoint).node_num == node_id)
            {
                pne = *edges;
                *edges = (*edges)->next;
                free(pne);
            }
        }
        ptr = &((*ptr)->next);      // forward the nodes pointer
    }

    pnode *ptr2 = head;
    if ((*ptr2)->node_num == node_id)
    {
        *ptr2 = (*ptr2)->next;
    }
    else{
        while ((*ptr2)->next->node_num != node_id)
        {
            ptr2 = &((*ptr2)->next);
        }
        (*ptr2)->next = ((*ptr2)->next)->next;
    }
    free(node);
    
    *ch = chptr;        // forward the data pointer
}

int min(int a, int b){
    /*
        return the minimum between two numbers
        a and b.
    */

    if (a < 0)
    {
        return b;
    }
    if (b < 0)
    {
        return a;
    }
    if (a < b)
    {
        return a;
    }
    else{
        return b;
    }
    
    
    
}


int findIndex(pnode head, int id){
    /*
        this method receive the id of the node and
        return its index in the arrays used in
        the functions below
    */
   pnode cpy = NULL;        // new
   cpy = head;
   if (id == -1)
   {
       return id;
   }
   int i = 0;
   while (cpy != NULL)
   {
       if ((*cpy).node_num < id)
       {
           i++;
       }
       cpy = (*cpy).next;
   }
   return i;
}


int findMin(int distance[], int visited[], int n){
    /*
        this method find the closest unvisited 
        node to src and return its index in the array
    */
    
    int min = 100000;
    int w = 0;
    for (int  i = 0; i < n; i++)
    {
        if ((visited[i] == 0) && (distance[i] < min) && (distance[i] > 0))
        {
            min = distance[i];
            w = i;
        }
    }
    return w;
}





int dijkstra(pnode head, int src, int dest){


    pnode counter = NULL;
    counter = head;
    int n = 0;      // number of odes in the graph

    int shortestPath = 0;       // the weight of the shortest path from src to dest

    //find the current size of the graph
    while (counter != NULL)
    {
        counter = counter->next;
        n++;
    }

    int adjList[n][n];      // adj list of the graph using 2D array
    // insert INF value at start
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adjList[i][j] = 100000;
        }
    }

    pnode nodes = NULL;
    nodes = head;
    pedge edges = NULL;
    int x = 0, y = 0;

    // insert the weights of the edges into the adj matrix
    while (nodes != NULL)
    {
        edges = (*nodes).edges;
        while (edges != NULL)
        {
            x = findIndex(head, nodes->node_num);
            y = findIndex(head, edges->endpoint->node_num);
            adjList[x][y] = edges->weight;
            edges = (*edges).next;
        }
        nodes = (*nodes).next;
    }

    // initilaize the visited array to zeros at start
    int visited[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    visited[src] = 1;       // mark the src node as visited

    //initilaize the distances from src to all the nodes
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

    int w = 0;
    for (int i = 0; i < n; i++)
    {
        w = findMin(distance, visited, n);
        visited[w] = 1;
        for (int v = 0; v < n; v++)
        {
            if (visited[v] == 0)
            {
                distance[v] = min(distance[v], distance[w] + adjList[w][v]);
            }
        }
    }
    
    shortestPath = distance[dest];
    return shortestPath;
}



void shortsPath_cmd(pnode head, char **ch){
    /*
    this method print the shortes path weight 
    from node src to node dest using
    dijkstra algorithm.
    time complexity of O(n*n)
    */
    char *chptr = *ch;

    int src = findIndex(head,toNum(&chptr));        // changed
    int dest = findIndex(head,toNum(&chptr));       // changed

    int weight = dijkstra(head, src, dest);

    if ((weight > 100000) || (weight < 0))
    {
        weight = -1;
    }
    

    printf("Dijkstra shortest path: %d\n", weight);
    *ch = chptr;
}



void swap(int *x, int *y){
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}

int shortsPath_array(pnode head, int cities[], int len){

    int sum = 0;
    for (int i = 0; i < len-1; i++)
    {
        if (sum >= 20000)
        {
            return sum;
        }
        sum += dijkstra(head, findIndex(head,cities[i]), findIndex(head,cities[i+1]));
    }
    return sum;

}

void permute(pnode head, int cities[], int start, int end, int size, int* fsum){

    int i = 0;
    if (start == end)
    {
        int sum = shortsPath_array(head, cities, size);
        if (min(sum, *fsum) == sum)
        {
            *fsum = sum;
        }
    }
    else{
        for (i = start; i <= end; i++)
        {
        swap((cities+start), (cities+i));
        permute(head, cities, start+1, end, size, fsum);
        swap((cities+start), (cities+i)); //backtrack
        }
    }

}
    



void TSP_cmd2(pnode head, char **ch){
    char *chptr = *ch;
    pnode counter = NULL;
    counter = head;
    int size = 0;       // number of nodes in the graph

    // find the current size of the graph
    while (counter != NULL)
    {
        counter = counter->next;
        size++;
    }

    int p = toNum(&chptr);      //number of cities to visit in tsp
    int cities[p];  
    int i = 0;
    // receive the list of the cities from the user
    while ((*chptr >= '0') && (*chptr <= '9'))
    {
        cities[i] = toNum(&chptr);
        i++;
    }

    int fsum = 100000;
    permute(head, cities, 0, p-1, p, &fsum);

    if ((fsum <= 0) || (fsum > 10000))
    {
        fsum = -1;
    }
    printf("TSP shortest path: %d\n", fsum);

    *ch = chptr;
}




